//
// Created by ljf on 24-8-16.
//

// You may need to build the project (run Qt uic code generator) to get "ui_widget.h" resolved

#include "widget.h"
#include "ui_widget.h"


widget::widget(QWidget *parent) :
        QWidget(parent), ui(new Ui::widget) {
    ui->setupUi(this);
    this->setAcceptDrops(true);
    thread = new PlayThread();
    connect(thread, SIGNAL(duration(int, int)), this, SLOT(onDuration(int, int)));
    connect(thread, SIGNAL(seekOk()), this, SLOT(onSeekOk()));
    void duration(long currentMs, long destMs);        //播放时长

    thread->start();

    sliderSeeking = false;
}

widget::~widget() {
    delete ui;
    thread->stop();
}

void widget::onSeekOk() {
    sliderSeeking = false;
}

void widget::onDuration(int currentMs, int destMs) {
    static int currentMs1 = -1, destMs1 = -1;
    if (currentMs1 == currentMs && destMs1 == destMs) return;
    currentMs1 = currentMs;
    destMs1 = destMs;
    qDebug() << "onDuration：" << currentMs << destMs << sliderSeeking;

    int currentSec = currentMs1 / 1000;
    int destSec = destMs1 / 1000;
    QString currentTime = QString("%1:%2:%3").arg(currentSec / 3600, 2, 10, QChar('0')).arg(currentSec % 3600 / 60, 2,
                                                                                            10, QChar('0')).arg(
            currentSec % 60, 2, 10, QChar('0'));

    QString destTime = QString("%1:%2:%3").arg(destSec / 3600, 2, 10, QChar('0')).arg(destSec % 3600 / 60, 2, 10,
                                                                                      QChar('0')).arg(destSec % 60, 2,
                                                                                                      10, QChar('0'));


    ui->label_duration->setText(currentTime + "/" + destTime);

    if (!sliderSeeking) //未滑动
    {
        ui->slider->setMaximum(destMs);
        ui->slider->setValue(currentMs);
    }
}

void widget::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasUrls())      //判断拖的类型
    {
        event->acceptProposedAction();
    }
    else
    {
        event->ignore();
    }
}

void widget::dropEvent(QDropEvent *event)
{
    if(event->mimeData()->hasUrls())        //判断放的类型
    {

        QList<QUrl> List = event->mimeData()->urls();

        if(List.length()!=0)
        {
            ui->line_audioPath->setText(List[0].toLocalFile());
        }

    }
    else
    {
        event->ignore();
    }
}


void widget::on_btn_start_clicked()
{

    sliderSeeking=false;

    thread->play(ui->line_audioPath->text());
    qDebug()<<ui->line_audioPath->text();
    qDebug()<<"btn_start_clicked";

}


void widget::on_btn_stop_clicked()
{
    thread->stop();
}

void widget::on_btn_pause_clicked()
{
    thread->pause();
}

void widget::on_btn_resume_clicked()
{
    thread->resume();
}


void widget::on_slider_sliderPressed()
{
    sliderSeeking=true;
}

void widget::on_slider_sliderReleased()
{

    thread->seek(ui->slider->value());

}

