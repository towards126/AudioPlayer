//
// Created by ljf on 24-8-16.
//

#ifndef AUDIOPLAYER_WIDGET_H
#define AUDIOPLAYER_WIDGET_H

#include <QWidget>
#include "playthread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class widget; }
QT_END_NAMESPACE

class widget : public QWidget {
Q_OBJECT

public:
    explicit widget(QWidget *parent = nullptr);

    ~widget() override;

    void dragEnterEvent(QDragEnterEvent *event);

    void dropEvent(QDropEvent *event);

    PlayThread *thread;


    bool sliderSeeking;      //滑动标志位,false:表示未seek,true:正在seek
private:
    Ui::widget *ui;
private slots:

    void on_btn_start_clicked();

    void on_btn_stop_clicked();

    void on_btn_pause_clicked();

    void on_btn_resume_clicked();

    void onDuration(int currentMs, int destMs);

    void onSeekOk();


    void on_slider_sliderPressed();

    void on_slider_sliderReleased();

signals:
    void valueChanged(int value);

};


#endif //AUDIOPLAYER_WIDGET_H
