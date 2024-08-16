//
// Created by ljf on 24-8-16.
//

#include "playthread.h"

#include <utility>

PlayThread::PlayThread() {
    audio = nullptr;

    type = control_none;
}

bool PlayThread::initAudio(int SampleRate) {
    QAudioFormat format;
    if (audio != nullptr) return true;
    format.setSampleRate(SampleRate);
    format.setChannelCount(2);
    format.setSampleFormat(QAudioFormat::Int16);
    auto audioDevice = QMediaDevices::defaultAudioOutput();
    if (!audioDevice.isFormatSupported(format)) {
        qWarning() << "Raw audio format not supported by backend, cannot play audio.";
        return false;
    }
    audio = new QAudioSink(format, this);
    audio->setBufferSize(10000);
    return true;
}

void PlayThread::play(QString filePath) {
    m_filePath = std::move(filePath);
    type = control_play;
    if (!this->isRunning()) this->start();
}

void PlayThread::stop() {

    if (this->isRunning()) {
        type = control_stop;
    }

}

void PlayThread::pause() {

    if (this->isRunning()) {
        type = control_pause;
    }

}

void PlayThread::resume() {
    if (this->isRunning()) {
        type = control_resume;
    }
}


void PlayThread::seek(int value) {

    if (this->isRunning()) {
        seekMs = value;
        type = control_seek;
    }
}

void PlayThread::debugErr(const QString &prefix, int err)  //根据错误编号获取错误信息并打印
{
    char errbuf[512] = {0};

    av_strerror(err, errbuf, sizeof(errbuf));

    qDebug() << prefix << ":" << errbuf;

    emit ERROR(prefix + ":" + errbuf);
}

void PlayThread::runPlay() {
    qDebug()<<"runplay";
    if (audio == nullptr) {
        emit ERROR("输出设备不支持该格式，不能播放音频");
        return;
    }
    AVFormatContext *formatContext = nullptr;
    auto ret = avformat_open_input(&formatContext, m_filePath.toStdString().c_str(), nullptr, nullptr);
    if (ret != 0) {
        debugErr("avformat_open_input", ret);
        return;
    }
    ret = avformat_find_stream_info(formatContext, nullptr);
    if (ret != 0) {
        debugErr("avformat_find_stream_info", ret);
        return;
    }
    int audioIndex = av_find_best_stream(formatContext, AVMEDIA_TYPE_AUDIO, -1, -1, nullptr, 0);
    qDebug() << "audioindex:" << audioIndex;
    auto *codec = avcodec_find_decoder(formatContext->streams[audioIndex]->codecpar->codec_id);
    auto *codecContext = avcodec_alloc_context3(codec);
    avcodec_parameters_to_context(codecContext, formatContext->streams[audioIndex]->codecpar);
    codecContext->pkt_timebase=formatContext->streams[audioIndex]->time_base;
    ret = avcodec_open2(codecContext, nullptr, nullptr);
    if (ret != 0) {
        debugErr("avcodec_open2", ret);
        return;
    }
    AVChannelLayout out_ch_layout = codecContext->ch_layout;

    SwrContext *swrctx = nullptr;
    swr_alloc_set_opts2(&swrctx, &out_ch_layout, AV_SAMPLE_FMT_S16, codecContext->sample_rate,
                        &codecContext->ch_layout, codecContext->sample_fmt, codecContext->sample_rate, 0, nullptr);
    swr_init(swrctx);

    int destMs =
            av_q2d(formatContext->streams[audioIndex]->time_base) * 1000 * formatContext->streams[audioIndex]->duration;
    qDebug() << "码率:" << codecContext->bit_rate;
    qDebug() << "格式:" << codecContext->sample_fmt;
    qDebug() << "采样率:" << codecContext->sample_rate;
    qDebug() << "时长:" << destMs;
    qDebug() << "解码器:" << codec->name;

    AVPacket *packet = av_packet_alloc();
    AVFrame *frame = av_frame_alloc();

    audio->stop();
    QIODevice *io = audio->start();
    while (1) {
        if (runIsBreak()) break;
        if (type == control_seek) {
            av_seek_frame(formatContext, audioIndex,
                          seekMs / (double) 1000 / av_q2d(formatContext->streams[audioIndex]->time_base),
                          AVSEEK_FLAG_BACKWARD);
            type = control_none;
            emit seekOk();
        }
        ret = av_read_frame(formatContext, packet);
        if (ret != 0) {
            debugErr("av_read_frame", ret);
            emit duration(destMs, destMs);
            break;
        }
        if (packet->stream_index == audioIndex) {
            ret = avcodec_send_packet(codecContext, packet);
            av_packet_unref(packet);
            if (ret != 0) {
                debugErr("avcodec_send_packet", ret);
                continue;
            }
            while (avcodec_receive_frame(codecContext, frame) == 0) {
                if (runIsBreak()) break;
                uint8_t *data= nullptr;
                int byteCnt = frame->nb_samples * 2 * 2;
                auto *pcm = new uint8_t[byteCnt];
                data = pcm;
                ret = swr_convert(swrctx, &pcm, frame->nb_samples*2, (const uint8_t **) frame->data, frame->nb_samples);
                int out_size = av_samples_get_buffer_size(0,
                                                          out_ch_layout.nb_channels,
                                                          ret,
                                                          AV_SAMPLE_FMT_S16,
                                                          1);
                int sleep_time=(codecContext->sample_rate*16/8)/out_size;
                while (audio->bytesFree() < byteCnt) {
                    if (runIsBreak()) break;
                    msleep(sleep_time);
                }
                if (!runIsBreak()) io->write((const char *) pcm, byteCnt);
                int currentMs = av_q2d(formatContext->streams[audioIndex]->time_base) * 1000 * frame->pts;
                //qDebug() << "时长:" << destMs << currentMs;
                emit duration(currentMs, destMs);

                delete[] pcm;
            }
        }
    }
    //释放内存
    av_frame_free(&frame);
    av_packet_free(&packet);
    swr_free(&swrctx);
    avcodec_free_context(&codecContext);
    avformat_close_input(&formatContext);
}

void PlayThread::run() {

    if (!initAudio(48000)) {
        emit ERROR("输出设备不支持该格式，不能播放音频");
    }

    while (1) {

        switch (type) {
            case control_none:
                msleep(100);
                break;
            case control_play :
                type = control_none;
                runPlay();
                break;    //播放
            default:
                type = control_none;
                break;
        }
    }

}

bool PlayThread::runIsBreak() {
    bool ret = false;
    //处理播放暂停
    if (type == control_pause) {
        while (type == control_pause) {
            audio->suspend();
            msleep(500);
        }

        if (type == control_resume) {
            audio->resume();
        }
    }

    if (type == control_play)    //重新播放
    {
        ret = true;
        if (audio->state() == QAudio::ActiveState)
            audio->stop();
    }

    if (type == control_stop)    //停止
    {
        ret = true;
        if (audio->state() == QAudio::ActiveState)
            audio->stop();
    }
    return ret;
}


