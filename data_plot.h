#ifndef _DATA_PLOT_H
#define _DATA_PLOT_H 1
#include <qwt_plot.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_zoomer.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_curve.h>
#include <qmutex.h>

const int PLOT_SIZE = 201;      // 0 to 200
#define SCHEDULE_STEP   		125
#define VISUAL_STEP   		(SCHEDULE_STEP << 3)
#define SCHEDULE_TXCONTROL_TM   0x06

class DataPlot : public QwtPlot
{
    Q_OBJECT

public:
    DataPlot(QWidget* = NULL);
    ~DataPlot();
    int get_signal_period(void);
    int get_signal_amplitude(void);
    int get_cntrl_err(void);
    int get_cntrl_up_tm(void);
    void full_screen(int on);

public slots:
    void view_wlevel_diagramm(float v, int control );
    void view_desired(int desired);
    void enableZoomMode(bool on);
    void reset_diagram(void);

private:
    int desired, accuracy, desired_min, desired_max;
    QwtPlotCurve *w_level;	
    double d_x[PLOT_SIZE]; 
    double d_y[PLOT_SIZE]; 
    double m0[PLOT_SIZE]; 
    double m1[PLOT_SIZE]; 
    double m2[PLOT_SIZE]; 
    void alignScales();
	int scan_extremp(int from);
	int scan_extremn(int from);	
	int up_tm_holded;
	int progress_tm;
    int cntrl_err, signal_amplitude, signal_period;
#if 0
    QwtPlotMarker *m0;
#endif
    QMutex mutex_0;
#if 0
    QwtPlotZoomer *d_zoomer[2];
#endif	
    QwtPlotPicker *d_picker;
    QwtPlotPanner *d_panner;
	
};

#endif
