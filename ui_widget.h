/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_widget
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QGridLayout *gridLayout;
    QLabel *label_duration;
    QLineEdit *line_audioPath;
    QLabel *label_11;
    QLabel *label_10;
    QLabel *label;
    QSlider *slider;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QSlider *slider_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *btn_start;
    QPushButton *btn_stop;
    QPushButton *btn_pause;
    QPushButton *btn_resume;

    void setupUi(QWidget *widget)
    {
        if (widget->objectName().isEmpty())
            widget->setObjectName("widget");
        widget->resize(400, 300);
        layoutWidget = new QWidget(widget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(40, 40, 332, 169));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        label_duration = new QLabel(layoutWidget);
        label_duration->setObjectName("label_duration");
        label_duration->setMinimumSize(QSize(0, 40));
        QFont font;
        font.setFamilies({QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221")});
        font.setPointSize(11);
        font.setBold(false);
        label_duration->setFont(font);

        gridLayout->addWidget(label_duration, 2, 1, 1, 1);

        line_audioPath = new QLineEdit(layoutWidget);
        line_audioPath->setObjectName("line_audioPath");
        line_audioPath->setMinimumSize(QSize(0, 40));

        gridLayout->addWidget(line_audioPath, 0, 1, 1, 1);

        label_11 = new QLabel(layoutWidget);
        label_11->setObjectName("label_11");
        label_11->setMinimumSize(QSize(0, 40));
        label_11->setFont(font);
        label_11->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        gridLayout->addWidget(label_11, 2, 0, 1, 1);

        label_10 = new QLabel(layoutWidget);
        label_10->setObjectName("label_10");
        label_10->setMinimumSize(QSize(0, 40));
        label_10->setFont(font);
        label_10->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        gridLayout->addWidget(label_10, 1, 0, 1, 1);

        label = new QLabel(layoutWidget);
        label->setObjectName("label");
        label->setMinimumSize(QSize(0, 40));
        label->setFont(font);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        slider = new QSlider(layoutWidget);
        slider->setObjectName("slider");
        slider->setMinimumSize(QSize(0, 40));
        slider->setMinimum(0);
        slider->setSingleStep(0);
        slider->setPageStep(0);
        slider->setOrientation(Qt::Orientation::Horizontal);

        gridLayout->addWidget(slider, 1, 1, 1, 1);


        horizontalLayout_2->addLayout(gridLayout);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName("label_2");
        label_2->setMinimumSize(QSize(0, 40));
        label_2->setFont(font);

        verticalLayout->addWidget(label_2);

        slider_2 = new QSlider(layoutWidget);
        slider_2->setObjectName("slider_2");
        slider_2->setMinimumSize(QSize(0, 40));
        slider_2->setMinimum(0);
        slider_2->setSingleStep(2);
        slider_2->setPageStep(10);
        slider_2->setValue(99);
        slider_2->setOrientation(Qt::Orientation::Vertical);

        verticalLayout->addWidget(slider_2, 0, Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignVCenter);


        horizontalLayout_2->addLayout(verticalLayout);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        btn_start = new QPushButton(layoutWidget);
        btn_start->setObjectName("btn_start");

        horizontalLayout->addWidget(btn_start);

        btn_stop = new QPushButton(layoutWidget);
        btn_stop->setObjectName("btn_stop");

        horizontalLayout->addWidget(btn_stop);

        btn_pause = new QPushButton(layoutWidget);
        btn_pause->setObjectName("btn_pause");

        horizontalLayout->addWidget(btn_pause);

        btn_resume = new QPushButton(layoutWidget);
        btn_resume->setObjectName("btn_resume");

        horizontalLayout->addWidget(btn_resume);


        verticalLayout_2->addLayout(horizontalLayout);


        retranslateUi(widget);

        QMetaObject::connectSlotsByName(widget);
    } // setupUi

    void retranslateUi(QWidget *widget)
    {
        widget->setWindowTitle(QCoreApplication::translate("widget", "widget", nullptr));
        label_duration->setText(QCoreApplication::translate("widget", "00:00:00/00:00:00", nullptr));
        label_11->setText(QCoreApplication::translate("widget", "\346\222\255\346\224\276\346\227\266\351\225\277:", nullptr));
        label_10->setText(QCoreApplication::translate("widget", "\346\222\255\346\224\276\350\277\233\345\272\246(\345\217\257\350\260\203):", nullptr));
        label->setText(QCoreApplication::translate("widget", "\351\237\263\351\242\221\350\267\257\345\276\204(\345\217\257\346\213\226\346\213\275):", nullptr));
        label_2->setText(QCoreApplication::translate("widget", "\345\243\260\351\237\263\345\244\247\345\260\217", nullptr));
        btn_start->setText(QCoreApplication::translate("widget", "\345\220\257\345\212\250", nullptr));
        btn_stop->setText(QCoreApplication::translate("widget", "\345\201\234\346\255\242", nullptr));
        btn_pause->setText(QCoreApplication::translate("widget", "\346\232\202\345\201\234", nullptr));
        btn_resume->setText(QCoreApplication::translate("widget", "\346\201\242\345\244\215", nullptr));
    } // retranslateUi

};

namespace Ui {
    class widget: public Ui_widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
