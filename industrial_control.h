#ifndef INDUSTRIAL_CONTROL_H
#define INDUSTRIAL_CONTROL_H
#include <QMainWindow>
#include <qtimer.h>
#include <qstring.h>
#include <qmutex.h>
#include <qlcdnumber.h>
#include <qspinbox.h>
#include <QDoubleSpinBox>
#define TXBUF_SIZE 256
#define RXBUF_SIZE 256
#define __WINDOWS__
#include <windows.h>
#include <QTime>
#include <QFile>
#include <qapplication.h>

#ifndef TPM101_v02
# define TPM101_MEASURE         0xB8DF /* Pv    ���������� �������� ������� �������� ( float24 ) */
# define TPM101_DESIRED         0x9107 /* Sp    ������� ���������� ( float24 ) */
# define TPM101_UP              0xAF90 /* r-S   ������/��������� �������������  1/0 ( u8 )*/
# define TPM101_OUT             0x35E8 /* o     ������������ �������� �������� �������� ���������� � %. ( float24 ) */
# define TPM101_OUTPUT          0x441A /* mvSt  �������� �������� �������� � ��������� "��������� �������������". ( float24 ) */

# define TPM101_KP       	0xFCFC /* p     ���� ������������������ ���-���������� ( float24 ) */
# define TPM101_KI       	0x5D6B /* i     ������������ ���������� ���-����������. ( float24 ) */
# define TPM101_KD       	0x2DFA /* d     ���������������� ���������� ���-����������. ( float24 ) */
# define TPM101_DAC       	0x8DF6 /* o-Ed  ��������������� �������� �������� �������� ( float24 ) */
# define TPM101_MANUAL    	0xD37D /* mdSt  ��������� ������ � ������ "��������� �������������". ( u9 ) */
# define TPM101_SENSOR          0x932D /* IN-T  ��� �������� ������� ��� ������� (��� ������  �����  9, ��������������= 50M, r428) */
# define TPM101_MIN_MEASURE     0xB040 /* IN-L* ������ ������� ��������� ��������� ( float24 ) */
# define TPM101_MAX_MEASURE     0x665D /* IN-H* ������� ������� ��������� ��������� ( float24 ) */
# define TPM101_MIN_DESIRED     0xABD3 /* SL-L* ������ ������� ������� ������� ( float24 ) */
# define TPM101_MAX_DESIRED     0x7DCE /* SL-H* ������� ������� ������� ������� ( float24 ) */
# define TPM101_B_MEASURE       0x39E8 /* SH*   ��������� ��������� "�����". ( float24 ) */
# define TPM101_K_MEASURE       0x39E8 /* KU*   ��������� ��������� "�����". ( float24 ) */
#endif

#define SEC_MS	1000
#define MIN_MS	(SEC_MS * 60)
#define HOUR_MS	(MIN_MS * 60)


namespace Ui {
    class industrial_control;
    class DataPlot;
}

class industrial_control : public QMainWindow {
    Q_OBJECT
public:
    industrial_control(QWidget *parent = 0);
    ~industrial_control();
protected:
    void changeEvent(QEvent *e);
    virtual void resizeEvent(QResizeEvent *event);
    virtual bool event(QEvent *event);
private:
    // magic begin there
    QList<QPoint> m_plotPoints;
    float get_level(QList<QPoint> points);
    float get_module(float value);
    int get_sign(float value);
    float get_error(QList<QPoint> points, float level);
    float get_amplitude(QList<QPoint> points);
    float get_period(QList<QPoint> points, float level);
    QList<QPoint> get_extremum(QList<QPoint> points);

    Ui::industrial_control *ui;
    QTimer *timer_1;
    QTimer *time1;
    QTimer *time2;
    QTimer *time3;
    QTimer *time4;
    QTimer *time5;
    QTimer *time6;
    QTimer *time7;
    QTimer *time8;
    QMutex mutex_1;

    float param;
    int profile_set;
    int schedule_tm;
    int record_count;
    int record_max;
    int record_now;
    QTime starttime;
    QTime difftime;
    QFile datafile;

    int rs232_tx_ok, rs232_tx_err, rs232_rx_ok, rs232_rx_err;
    int full_screen;
    HANDLE rs232;
    int rs232_init(QString port_name);
    void set_enable(bool v);
    void rs232_release(void);
    void log_add_str( QString s );
    unsigned short mb_crc16( unsigned char *buf, unsigned short len );
    int rs232_rx(unsigned char *rx_buf, unsigned int nbytes);
    int rs232_tx(unsigned char *tx_buf, unsigned int tx_len);
    unsigned short owenCRC16(unsigned char* packet, int length);
    void initFastCRC16Table(void);
    unsigned short owenFastCRC16(unsigned char* packet, int length);
    int packFrameToAscii(unsigned char* frame, int frameSize, unsigned char* frameAscii, int frameAsciiSize);
    int unpackAsciiFrame(unsigned char* frameAscii, int frameAsciiSize, unsigned char* frame, int frameSize);
    int appendIndexAndTime(struct rs485_packet* pf, short index, short time);
    int packFrame(struct rs485_packet* pf, unsigned char* frame, int max_frame_size);
    int unpackFrame(unsigned char* frame, int frameSize, struct rs485_packet* pf);
    int unpackFloat24(unsigned char* data, int dataSize, float* value);
    int pack_float24(unsigned char* data, float v);
    int unpackIEEE32(unsigned char* data, int dataSize, float* v, int *time);
    int unpackBCD(unsigned char* data, int dataSize, int* v, int *point);
    int name2id(char* name, int length, unsigned char id[4]);
    unsigned short id2hash(unsigned char id[4]);
    int tx_oven_req(struct rs485_packet *pf);
    int rx_oven_frame(struct rs485_packet *pf);
    void log_oven_err(struct rs485_packet *pf);

private slots:
    int interface_start(void);
    void interface_stop(void);
    void quit(void);
    int scheduler(void);

    int profile1(void);
    int profile2(void);
    int profile3(void);
    int profile4(void);
    int profile5(void);
    int profile6(void);
    int profile0(void);
    int record(void);

    void set_desired_t(void);
    void set_kp(void);
    void set_kd(void);
    void set_ki(void);
    void set_auto(void);
    void set_out(void);
    void resize_form(bool full_scr);
};

#endif // INDUSTRIAL_CONTROL_H
