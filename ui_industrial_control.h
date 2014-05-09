/********************************************************************************
** Form generated from reading ui file 'industrial_control.ui'
**
** Created: Thu 7. Jun 16:31:49 2012
**      by: Qt User Interface Compiler version 4.5.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_INDUSTRIAL_CONTROL_H
#define UI_INDUSTRIAL_CONTROL_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpinBox>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_industrial_control
{
public:
    QWidget *centralWidget;
    QGroupBox *group_3;
    QLabel *mii_label_0;
    QLabel *mii_label_3;
    QSpinBox *rs232_ch;
    QFrame *led_rs232;
    QGroupBox *group_1;
    QLabel *label_8;
    QSpinBox *desired_t;
    QLabel *label_12;
    QLabel *label_10;
    QLabel *label_kd;
    QLCDNumber *lcd_t;
    QLabel *label_7;
    QSpinBox *Kp;
    QSpinBox *Ki;
    QSpinBox *Kd;
    QGroupBox *group_2;
    QLCDNumber *lcd_o;
    QLabel *label_11;
    QSpinBox *heater_productivity;
    QGroupBox *group_4;
    QFrame *led_pid;
    QRadioButton *heater_pid;
    QRadioButton *heater_manual;
    QFrame *led_manual;
    QRadioButton *heater_off;
    QFrame *led_off;
    QGroupBox *group_5;
    QGroupBox *group_6;
    QLabel *label_15;
    QLCDNumber *lcd_signal_period;
    QLCDNumber *lcd_signal_amplitude;
    QLabel *label_16;
    QLabel *label_14;
    QLCDNumber *lcd_cntrl_up_tm;
    QLabel *label_18;
    QLCDNumber *lcd_cntrl_err;
    QPushButton *button_exit;
    QPushButton *button_stop;
    QPushButton *button_start;
    QGroupBox *groupBox;
    QSpinBox *desired1;
    QLabel *label_9;
    QLabel *label_13;
    QSpinBox *desired3;
    QSpinBox *desired4;
    QLabel *label_19;
    QSpinBox *desired5;
    QLabel *label_20;
    QSpinBox *desired6;
    QLabel *label_21;
    QLabel *label_17;
    QSpinBox *tim1;
    QSpinBox *tim2;
    QSpinBox *tim3;
    QSpinBox *tim4;
    QSpinBox *tim5;
    QSpinBox *tim6;
    QFrame *line;
    QFrame *line_2;
    QSpinBox *desired2;
    QGroupBox *groupBox_2;
    QLabel *labe;
    QLabel *label;
    QLabel *labe_2;
    QSpinBox *vremzap;
    QLabel *labe_3;
    QSpinBox *kolzap;

    void setupUi(QMainWindow *industrial_control)
    {
        if (industrial_control->objectName().isEmpty())
            industrial_control->setObjectName(QString::fromUtf8("industrial_control"));
        industrial_control->setWindowModality(Qt::NonModal);
        industrial_control->setEnabled(true);
        industrial_control->resize(920, 567);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(industrial_control->sizePolicy().hasHeightForWidth());
        industrial_control->setSizePolicy(sizePolicy);
        industrial_control->setMinimumSize(QSize(920, 567));
        industrial_control->setMaximumSize(QSize(920, 567));
        industrial_control->setBaseSize(QSize(920, 567));
        centralWidget = new QWidget(industrial_control);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        group_3 = new QGroupBox(centralWidget);
        group_3->setObjectName(QString::fromUtf8("group_3"));
        group_3->setGeometry(QRect(10, 330, 241, 81));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        group_3->setFont(font);
        mii_label_0 = new QLabel(group_3);
        mii_label_0->setObjectName(QString::fromUtf8("mii_label_0"));
        mii_label_0->setGeometry(QRect(10, 50, 81, 20));
        QFont font1;
        font1.setBold(false);
        font1.setWeight(50);
        mii_label_0->setFont(font1);
        mii_label_0->setWordWrap(false);
        mii_label_3 = new QLabel(group_3);
        mii_label_3->setObjectName(QString::fromUtf8("mii_label_3"));
        mii_label_3->setGeometry(QRect(10, 20, 61, 20));
        mii_label_3->setFont(font1);
        mii_label_3->setWordWrap(false);
        rs232_ch = new QSpinBox(group_3);
        rs232_ch->setObjectName(QString::fromUtf8("rs232_ch"));
        rs232_ch->setGeometry(QRect(170, 20, 61, 22));
        rs232_ch->setFont(font1);
        rs232_ch->setMinimum(1);
        rs232_ch->setMaximum(2);
        led_rs232 = new QFrame(group_3);
        led_rs232->setObjectName(QString::fromUtf8("led_rs232"));
        led_rs232->setGeometry(QRect(190, 50, 21, 21));
        led_rs232->setFont(font1);
        led_rs232->setAutoFillBackground(true);
        led_rs232->setFrameShape(QFrame::StyledPanel);
        led_rs232->setFrameShadow(QFrame::Raised);
        group_1 = new QGroupBox(centralWidget);
        group_1->setObjectName(QString::fromUtf8("group_1"));
        group_1->setGeometry(QRect(10, 10, 241, 171));
        group_1->setFont(font);
        label_8 = new QLabel(group_1);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(10, 50, 71, 16));
        label_8->setFont(font1);
        desired_t = new QSpinBox(group_1);
        desired_t->setObjectName(QString::fromUtf8("desired_t"));
        desired_t->setGeometry(QRect(170, 50, 61, 22));
        desired_t->setFont(font1);
        desired_t->setMinimum(40);
        desired_t->setMaximum(100);
        desired_t->setValue(40);
        label_12 = new QLabel(group_1);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(10, 110, 61, 16));
        label_12->setFont(font1);
        label_10 = new QLabel(group_1);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(10, 80, 61, 16));
        label_10->setFont(font1);
        label_kd = new QLabel(group_1);
        label_kd->setObjectName(QString::fromUtf8("label_kd"));
        label_kd->setGeometry(QRect(10, 140, 61, 16));
        label_kd->setFont(font1);
        lcd_t = new QLCDNumber(group_1);
        lcd_t->setObjectName(QString::fromUtf8("lcd_t"));
        lcd_t->setGeometry(QRect(170, 20, 61, 21));
        QPalette palette;
        QBrush brush(QColor(0, 170, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        QBrush brush1(QColor(106, 104, 100, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        lcd_t->setPalette(palette);
        QFont font2;
        font2.setBold(false);
        font2.setItalic(true);
        font2.setWeight(50);
        lcd_t->setFont(font2);
        lcd_t->setSmallDecimalPoint(false);
        lcd_t->setNumDigits(5);
        lcd_t->setMode(QLCDNumber::Dec);
        lcd_t->setSegmentStyle(QLCDNumber::Flat);
        lcd_t->setProperty("value", QVariant(0));
        label_7 = new QLabel(group_1);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(10, 20, 91, 20));
        label_7->setFont(font1);
        Kp = new QSpinBox(group_1);
        Kp->setObjectName(QString::fromUtf8("Kp"));
        Kp->setGeometry(QRect(170, 80, 61, 22));
        Kp->setFont(font1);
        Kp->setMinimum(0);
        Kp->setMaximum(9999);
        Kp->setValue(1);
        Ki = new QSpinBox(group_1);
        Ki->setObjectName(QString::fromUtf8("Ki"));
        Ki->setGeometry(QRect(170, 110, 61, 22));
        Ki->setFont(font1);
        Ki->setMaximum(3999);
        Kd = new QSpinBox(group_1);
        Kd->setObjectName(QString::fromUtf8("Kd"));
        Kd->setGeometry(QRect(170, 140, 61, 22));
        Kd->setFont(font1);
        Kd->setMaximum(3999);
        group_2 = new QGroupBox(centralWidget);
        group_2->setObjectName(QString::fromUtf8("group_2"));
        group_2->setGeometry(QRect(10, 270, 241, 51));
        group_2->setFont(font);
        lcd_o = new QLCDNumber(group_2);
        lcd_o->setObjectName(QString::fromUtf8("lcd_o"));
        lcd_o->setGeometry(QRect(180, 20, 51, 21));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        lcd_o->setPalette(palette1);
        lcd_o->setFont(font2);
        lcd_o->setSmallDecimalPoint(false);
        lcd_o->setNumDigits(3);
        lcd_o->setMode(QLCDNumber::Dec);
        lcd_o->setSegmentStyle(QLCDNumber::Flat);
        lcd_o->setProperty("value", QVariant(0));
        label_11 = new QLabel(group_2);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(10, 20, 81, 16));
        label_11->setFont(font1);
        heater_productivity = new QSpinBox(group_2);
        heater_productivity->setObjectName(QString::fromUtf8("heater_productivity"));
        heater_productivity->setEnabled(false);
        heater_productivity->setGeometry(QRect(110, 20, 61, 21));
        heater_productivity->setFont(font1);
        heater_productivity->setMaximum(100);
        group_4 = new QGroupBox(centralWidget);
        group_4->setObjectName(QString::fromUtf8("group_4"));
        group_4->setGeometry(QRect(10, 180, 241, 81));
        group_4->setFont(font);
        led_pid = new QFrame(group_4);
        led_pid->setObjectName(QString::fromUtf8("led_pid"));
        led_pid->setGeometry(QRect(10, 20, 16, 16));
        led_pid->setFont(font1);
        led_pid->setAutoFillBackground(true);
        led_pid->setFrameShape(QFrame::StyledPanel);
        led_pid->setFrameShadow(QFrame::Raised);
        heater_pid = new QRadioButton(group_4);
        heater_pid->setObjectName(QString::fromUtf8("heater_pid"));
        heater_pid->setGeometry(QRect(50, 20, 101, 18));
        heater_pid->setFont(font1);
        heater_pid->setChecked(true);
        heater_manual = new QRadioButton(group_4);
        heater_manual->setObjectName(QString::fromUtf8("heater_manual"));
        heater_manual->setGeometry(QRect(50, 40, 101, 18));
        heater_manual->setFont(font1);
        led_manual = new QFrame(group_4);
        led_manual->setObjectName(QString::fromUtf8("led_manual"));
        led_manual->setGeometry(QRect(10, 40, 16, 16));
        led_manual->setFont(font1);
        led_manual->setAutoFillBackground(true);
        led_manual->setFrameShape(QFrame::StyledPanel);
        led_manual->setFrameShadow(QFrame::Raised);
        heater_off = new QRadioButton(group_4);
        heater_off->setObjectName(QString::fromUtf8("heater_off"));
        heater_off->setGeometry(QRect(50, 60, 101, 18));
        heater_off->setFont(font1);
        heater_off->setChecked(false);
        led_off = new QFrame(group_4);
        led_off->setObjectName(QString::fromUtf8("led_off"));
        led_off->setGeometry(QRect(10, 60, 16, 16));
        led_off->setFont(font1);
        led_off->setAutoFillBackground(true);
        led_off->setFrameShape(QFrame::StyledPanel);
        led_off->setFrameShadow(QFrame::Raised);
        group_5 = new QGroupBox(centralWidget);
        group_5->setObjectName(QString::fromUtf8("group_5"));
        group_5->setGeometry(QRect(260, 10, 641, 451));
        group_5->setFlat(false);
        group_6 = new QGroupBox(centralWidget);
        group_6->setObjectName(QString::fromUtf8("group_6"));
        group_6->setGeometry(QRect(10, 420, 241, 141));
        group_6->setFont(font);
        label_15 = new QLabel(group_6);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(10, 110, 131, 16));
        label_15->setFont(font1);
        lcd_signal_period = new QLCDNumber(group_6);
        lcd_signal_period->setObjectName(QString::fromUtf8("lcd_signal_period"));
        lcd_signal_period->setGeometry(QRect(170, 110, 61, 21));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        lcd_signal_period->setPalette(palette2);
        lcd_signal_period->setFont(font2);
        lcd_signal_period->setSmallDecimalPoint(false);
        lcd_signal_period->setNumDigits(6);
        lcd_signal_period->setMode(QLCDNumber::Dec);
        lcd_signal_period->setSegmentStyle(QLCDNumber::Flat);
        lcd_signal_period->setProperty("value", QVariant(0));
        lcd_signal_amplitude = new QLCDNumber(group_6);
        lcd_signal_amplitude->setObjectName(QString::fromUtf8("lcd_signal_amplitude"));
        lcd_signal_amplitude->setGeometry(QRect(170, 50, 61, 21));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        lcd_signal_amplitude->setPalette(palette3);
        lcd_signal_amplitude->setFont(font2);
        lcd_signal_amplitude->setSmallDecimalPoint(false);
        lcd_signal_amplitude->setNumDigits(5);
        lcd_signal_amplitude->setMode(QLCDNumber::Dec);
        lcd_signal_amplitude->setSegmentStyle(QLCDNumber::Flat);
        lcd_signal_amplitude->setProperty("value", QVariant(0));
        label_16 = new QLabel(group_6);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(10, 50, 141, 16));
        label_16->setFont(font1);
        label_14 = new QLabel(group_6);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(10, 80, 171, 16));
        label_14->setFont(font1);
        lcd_cntrl_up_tm = new QLCDNumber(group_6);
        lcd_cntrl_up_tm->setObjectName(QString::fromUtf8("lcd_cntrl_up_tm"));
        lcd_cntrl_up_tm->setGeometry(QRect(170, 80, 61, 21));
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette4.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        lcd_cntrl_up_tm->setPalette(palette4);
        lcd_cntrl_up_tm->setFont(font2);
        lcd_cntrl_up_tm->setSmallDecimalPoint(false);
        lcd_cntrl_up_tm->setNumDigits(6);
        lcd_cntrl_up_tm->setMode(QLCDNumber::Dec);
        lcd_cntrl_up_tm->setSegmentStyle(QLCDNumber::Flat);
        lcd_cntrl_up_tm->setProperty("value", QVariant(0));
        label_18 = new QLabel(group_6);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(10, 20, 111, 16));
        label_18->setFont(font1);
        lcd_cntrl_err = new QLCDNumber(group_6);
        lcd_cntrl_err->setObjectName(QString::fromUtf8("lcd_cntrl_err"));
        lcd_cntrl_err->setGeometry(QRect(170, 20, 61, 21));
        QPalette palette5;
        palette5.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette5.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        lcd_cntrl_err->setPalette(palette5);
        lcd_cntrl_err->setFont(font2);
        lcd_cntrl_err->setFrameShape(QFrame::Box);
        lcd_cntrl_err->setSmallDecimalPoint(false);
        lcd_cntrl_err->setNumDigits(5);
        lcd_cntrl_err->setMode(QLCDNumber::Dec);
        lcd_cntrl_err->setSegmentStyle(QLCDNumber::Flat);
        lcd_cntrl_err->setProperty("value", QVariant(0));
        button_exit = new QPushButton(centralWidget);
        button_exit->setObjectName(QString::fromUtf8("button_exit"));
        button_exit->setGeometry(QRect(790, 530, 111, 31));
        QFont font3;
        font3.setBold(true);
        font3.setUnderline(false);
        font3.setWeight(75);
        font3.setStrikeOut(false);
        button_exit->setFont(font3);
        button_exit->setCursor(QCursor(Qt::WhatsThisCursor));
        button_stop = new QPushButton(centralWidget);
        button_stop->setObjectName(QString::fromUtf8("button_stop"));
        button_stop->setGeometry(QRect(790, 500, 111, 31));
        button_stop->setCursor(QCursor(Qt::PointingHandCursor));
        button_start = new QPushButton(centralWidget);
        button_start->setObjectName(QString::fromUtf8("button_start"));
        button_start->setGeometry(QRect(790, 470, 111, 31));
        button_start->setCursor(QCursor(Qt::PointingHandCursor));
        button_start->setCheckable(false);
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(260, 460, 311, 101));
        groupBox->setFont(font);
        desired1 = new QSpinBox(groupBox);
        desired1->setObjectName(QString::fromUtf8("desired1"));
        desired1->setGeometry(QRect(110, 30, 41, 22));
        desired1->setFont(font1);
        desired1->setMinimum(40);
        desired1->setMaximum(100);
        desired1->setValue(40);
        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(10, 30, 20, 20));
        QFont font4;
        font4.setPointSize(8);
        font4.setBold(false);
        font4.setWeight(50);
        label_9->setFont(font4);
        label_13 = new QLabel(groupBox);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(10, 50, 21, 16));
        label_13->setFont(font4);
        desired3 = new QSpinBox(groupBox);
        desired3->setObjectName(QString::fromUtf8("desired3"));
        desired3->setGeometry(QRect(110, 70, 41, 22));
        desired3->setFont(font1);
        desired3->setMinimum(40);
        desired3->setMaximum(100);
        desired3->setValue(40);
        desired4 = new QSpinBox(groupBox);
        desired4->setObjectName(QString::fromUtf8("desired4"));
        desired4->setGeometry(QRect(260, 30, 41, 22));
        desired4->setFont(font1);
        desired4->setMinimum(40);
        desired4->setMaximum(100);
        desired4->setValue(40);
        label_19 = new QLabel(groupBox);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setGeometry(QRect(160, 30, 20, 20));
        label_19->setFont(font1);
        desired5 = new QSpinBox(groupBox);
        desired5->setObjectName(QString::fromUtf8("desired5"));
        desired5->setGeometry(QRect(260, 50, 41, 22));
        desired5->setFont(font1);
        desired5->setMinimum(40);
        desired5->setMaximum(100);
        desired5->setValue(40);
        label_20 = new QLabel(groupBox);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setGeometry(QRect(160, 50, 21, 16));
        label_20->setFont(font1);
        desired6 = new QSpinBox(groupBox);
        desired6->setObjectName(QString::fromUtf8("desired6"));
        desired6->setGeometry(QRect(260, 70, 41, 21));
        desired6->setFont(font1);
        desired6->setMinimum(40);
        desired6->setMaximum(100);
        desired6->setValue(40);
        label_21 = new QLabel(groupBox);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setGeometry(QRect(160, 70, 20, 20));
        label_21->setFont(font1);
        label_17 = new QLabel(groupBox);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(10, 70, 21, 16));
        label_17->setFont(font4);
        tim1 = new QSpinBox(groupBox);
        tim1->setObjectName(QString::fromUtf8("tim1"));
        tim1->setGeometry(QRect(30, 30, 61, 22));
        tim1->setFont(font1);
        tim1->setMaximum(10000);
        tim1->setValue(0);
        tim2 = new QSpinBox(groupBox);
        tim2->setObjectName(QString::fromUtf8("tim2"));
        tim2->setGeometry(QRect(30, 50, 61, 22));
        tim2->setFont(font1);
        tim2->setMaximum(10000);
        tim2->setValue(0);
        tim3 = new QSpinBox(groupBox);
        tim3->setObjectName(QString::fromUtf8("tim3"));
        tim3->setGeometry(QRect(30, 70, 61, 22));
        tim3->setFont(font1);
        tim3->setMaximum(10000);
        tim3->setValue(0);
        tim4 = new QSpinBox(groupBox);
        tim4->setObjectName(QString::fromUtf8("tim4"));
        tim4->setGeometry(QRect(180, 30, 61, 22));
        tim4->setFont(font1);
        tim4->setMaximum(10000);
        tim4->setValue(0);
        tim5 = new QSpinBox(groupBox);
        tim5->setObjectName(QString::fromUtf8("tim5"));
        tim5->setGeometry(QRect(180, 50, 61, 22));
        tim5->setFont(font1);
        tim5->setMaximum(10000);
        tim5->setValue(0);
        tim6 = new QSpinBox(groupBox);
        tim6->setObjectName(QString::fromUtf8("tim6"));
        tim6->setGeometry(QRect(180, 70, 61, 22));
        tim6->setFont(font1);
        tim6->setMaximum(10000);
        tim6->setValue(0);
        line = new QFrame(groupBox);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(90, 30, 16, 61));
        line->setFrameShadow(QFrame::Raised);
        line->setLineWidth(1);
        line->setFrameShape(QFrame::VLine);
        line_2 = new QFrame(groupBox);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(240, 30, 16, 61));
        line_2->setFrameShadow(QFrame::Raised);
        line_2->setLineWidth(1);
        line_2->setFrameShape(QFrame::VLine);
        desired2 = new QSpinBox(groupBox);
        desired2->setObjectName(QString::fromUtf8("desired2"));
        desired2->setGeometry(QRect(110, 50, 41, 22));
        desired2->setFont(font1);
        desired2->setMinimum(40);
        desired2->setMaximum(100);
        desired2->setValue(40);
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(580, 460, 201, 101));
        groupBox_2->setFont(font);
        labe = new QLabel(groupBox_2);
        labe->setObjectName(QString::fromUtf8("labe"));
        labe->setGeometry(QRect(10, 40, 151, 20));
        labe->setFont(font1);
        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 20, 151, 20));
        label->setFont(font1);
        labe_2 = new QLabel(groupBox_2);
        labe_2->setObjectName(QString::fromUtf8("labe_2"));
        labe_2->setGeometry(QRect(10, 60, 121, 20));
        labe_2->setFont(font1);
        vremzap = new QSpinBox(groupBox_2);
        vremzap->setObjectName(QString::fromUtf8("vremzap"));
        vremzap->setGeometry(QRect(140, 60, 51, 16));
        vremzap->setFont(font1);
        vremzap->setMaximum(1000);
        vremzap->setValue(0);
        labe_3 = new QLabel(groupBox_2);
        labe_3->setObjectName(QString::fromUtf8("labe_3"));
        labe_3->setGeometry(QRect(10, 80, 131, 20));
        labe_3->setFont(font1);
        kolzap = new QSpinBox(groupBox_2);
        kolzap->setObjectName(QString::fromUtf8("kolzap"));
        kolzap->setGeometry(QRect(140, 80, 51, 16));
        kolzap->setFont(font1);
        kolzap->setMaximum(10000);
        kolzap->setValue(0);
        industrial_control->setCentralWidget(centralWidget);

        retranslateUi(industrial_control);
        QObject::connect(button_exit, SIGNAL(pressed()), industrial_control, SLOT(quit()));
        QObject::connect(button_start, SIGNAL(pressed()), industrial_control, SLOT(interface_start()));
        QObject::connect(button_stop, SIGNAL(pressed()), industrial_control, SLOT(interface_stop()));
        QObject::connect(desired_t, SIGNAL(editingFinished()), industrial_control, SLOT(set_desired_t()));
        QObject::connect(heater_off, SIGNAL(clicked()), industrial_control, SLOT(set_auto()));
        QObject::connect(heater_pid, SIGNAL(clicked()), industrial_control, SLOT(set_auto()));
        QObject::connect(heater_manual, SIGNAL(clicked()), industrial_control, SLOT(set_auto()));
        QObject::connect(heater_productivity, SIGNAL(editingFinished()), industrial_control, SLOT(set_out()));

        QMetaObject::connectSlotsByName(industrial_control);
    } // setupUi

    void retranslateUi(QMainWindow *industrial_control)
    {
        industrial_control->setWindowTitle(QApplication::translate("industrial_control", "\320\237\321\200\320\276\320\274\321\213\321\210\320\273\320\265\320\275\320\275\320\260\321\217 \320\260\320\262\321\202\320\276\320\274\320\260\321\202\320\270\320\267\320\260\321\206\320\270\321\217", 0, QApplication::UnicodeUTF8));
        group_3->setTitle(QApplication::translate("industrial_control", "\320\230\320\275\321\202\320\265\321\200\321\204\320\265\320\271\321\201 \321\201 \321\200\320\265\320\263\321\203\320\273\321\217\321\202\320\276\321\200\320\276\320\274:", 0, QApplication::UnicodeUTF8));
        mii_label_0->setText(QApplication::translate("industrial_control", "\320\241\320\276\320\265\320\264\320\270\320\275\320\265\320\275\320\270\320\265:", 0, QApplication::UnicodeUTF8));
        mii_label_3->setText(QApplication::translate("industrial_control", "\320\237\320\276\321\200\321\202: COM", 0, QApplication::UnicodeUTF8));
        group_1->setTitle(QApplication::translate("industrial_control", "\320\240\320\265\320\263\321\203\320\273\320\270\321\200\320\276\320\262\320\260\320\275\320\270\320\265:", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("industrial_control", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">\320\243\321\201\321\202\320\260\320\262\320\272\320\260,</span><span style=\" font-size:8pt; vertical-align:super;\">\320\276</span><span style=\" font-size:8pt;\">\320\241:</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("industrial_control", "Ki", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("industrial_control", "Kp", 0, QApplication::UnicodeUTF8));
        label_kd->setText(QApplication::translate("industrial_control", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Kd:</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("industrial_control", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">\320\242\320\265\320\274\320\277\320\265\321\200\320\260\321\202\321\203\321\200\320\260,</span><span style=\" font-size:8pt; vertical-align:super;\">\320\276</span><span style=\" font-size:8pt;\">\320\241:</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        group_2->setTitle(QApplication::translate("industrial_control", "\320\235\320\260\320\263\321\200\320\265\320\262\320\260\321\202\320\265\320\273\321\214:", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("industrial_control", "\320\234\320\276\321\211\320\275\320\276\321\201\321\202\321\214, %:", 0, QApplication::UnicodeUTF8));
        group_4->setTitle(QApplication::translate("industrial_control", "\320\240\320\265\320\266\320\270\320\274 \321\200\320\265\320\263\321\203\320\273\320\270\321\200\320\276\320\262\320\260\320\275\320\270\321\217:", 0, QApplication::UnicodeUTF8));
        heater_pid->setText(QApplication::translate("industrial_control", "\320\275\320\265\320\277\321\200\320\265\321\200\321\213\320\262\320\275\320\276\320\265", 0, QApplication::UnicodeUTF8));
        heater_manual->setText(QApplication::translate("industrial_control", "\321\200\321\203\321\207\320\275\320\276\320\271", 0, QApplication::UnicodeUTF8));
        heater_off->setText(QApplication::translate("industrial_control", "\320\262\321\213\320\272\320\273\321\216\321\207\320\265\320\275\320\276", 0, QApplication::UnicodeUTF8));
        group_5->setTitle(QApplication::translate("industrial_control", "\320\242\320\265\320\274\320\277\320\265\321\200\320\260\321\202\321\203\321\200\320\260:", 0, QApplication::UnicodeUTF8));
        group_6->setTitle(QApplication::translate("industrial_control", "\320\237\320\276\320\272\320\260\320\267\320\260\321\202\320\265\320\273\320\270 \320\272\320\260\321\207\320\265\321\201\321\202\320\262\320\260 \321\200\320\265\320\263\321\203\320\273\320\270\321\200\320\276\320\262\320\260\320\275\320\270\321\217:", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("industrial_control", "\320\237\320\265\321\200\320\270\320\276\320\264 \320\272\320\276\320\273\320\265\320\261\320\260\320\275\320\270\320\271,\321\201\320\265\320\272:", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("industrial_control", "\320\220\320\274\320\277\320\273\320\270\321\202\321\203\320\264\320\260 \320\272\320\276\320\273\320\265\320\261\320\260\320\275\320\270\320\271,\320\274\320\274:", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("industrial_control", "\320\222\321\200\320\265\320\274\321\217 \320\262\321\213\321\205\320\276\320\264\320\260 \320\275\320\260 \321\203\321\201\321\202\320\260\320\262\320\272\321\203, \321\201\320\265\320\272:", 0, QApplication::UnicodeUTF8));
        label_18->setText(QApplication::translate("industrial_control", "\320\236\321\210\320\270\320\261\320\272\320\260 \321\200\320\265\320\263\321\203\320\273\320\270\321\200,\320\274\320\274:", 0, QApplication::UnicodeUTF8));
        button_exit->setText(QApplication::translate("industrial_control", "\320\222\321\213\321\205\320\276\320\264", 0, QApplication::UnicodeUTF8));
        button_stop->setText(QApplication::translate("industrial_control", "\320\241\321\202\320\276\320\277", 0, QApplication::UnicodeUTF8));
        button_start->setText(QApplication::translate("industrial_control", "\320\241\321\202\320\260\321\200\321\202", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("industrial_control", "\320\237\321\200\320\276\321\204\320\270\320\273\320\270 (\320\262\321\200\320\265\320\274\321\217, \321\201\320\265\320\272. - \321\202\320\265\320\274\320\277\320\265\321\200\320\260\321\202\321\203\321\200\320\260, '\320\241)", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("industrial_control", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">1:</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("industrial_control", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">2:</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_19->setText(QApplication::translate("industrial_control", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">4:</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_20->setText(QApplication::translate("industrial_control", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">5:</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_21->setText(QApplication::translate("industrial_control", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">6:</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("industrial_control", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">3:</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("industrial_control", "\320\241\320\276\321\201\321\202\320\276\321\217\320\275\320\270\320\265 \321\200\320\260\320\261\320\276\321\202\321\213", 0, QApplication::UnicodeUTF8));
        labe->setText(QApplication::translate("industrial_control", "\320\222\321\200\320\265\320\274\321\217 \321\200\320\260\320\261\320\276\321\202\321\213 \320\277\320\276\321\201\320\273\320\265 \321\201\321\202\320\260\321\200\321\202\320\260", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("industrial_control", "\320\220\320\272\321\202\320\270\320\262\320\275\321\213\320\271 \320\277\321\200\320\276\321\204\320\270\320\273\321\214", 0, QApplication::UnicodeUTF8));
        labe_2->setText(QApplication::translate("industrial_control", "\320\247\320\260\321\201\321\202\320\276\321\202\320\260 \320\267\320\260\320\277\320\270\321\201\320\270 (\321\201\320\265\320\272):", 0, QApplication::UnicodeUTF8));
        labe_3->setText(QApplication::translate("industrial_control", "\320\232\320\276\320\273-\320\262\320\276 \320\267\320\260\320\277\320\270\321\201\320\265\320\271 \320\262 \321\204\320\260\320\271\320\273\320\265:", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(industrial_control);
    } // retranslateUi

};

namespace Ui {
    class industrial_control: public Ui_industrial_control {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INDUSTRIAL_CONTROL_H
