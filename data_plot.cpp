#include <stdlib.h>
#include <qwt_painter.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_curve.h>
#include <qwt_scale_widget.h>
#include <qwt_legend.h>
#include <qwt_plot_grid.h>
#include <qwt_scale_draw.h>
#include <qwt_scale_div.h>
#include <qwt_text.h>
#include <qdebug.h>
#include <qstring.h>
#include <qfont.h>
#include <qtoolbar.h>
#include <QPointF>
#include <qtoolbutton.h>
#include <QMainWindow>
#if QT_VERSION >= 0x040000
#include <qprintdialog.h>
#include <qfileinfo.h>
#else
#include <qwt_painter.h>
#endif

#include "data_plot.h"

/*================================================================================================*/

/*  Initialize main window */
DataPlot::DataPlot(QWidget *parent): QwtPlot(parent)
{QwtPainter::setDeviceClipping(false); 
 QFont f("MS Sans Serif");
 canvas()->setPaintAttribute(QwtPlotCanvas::PaintCached, false);
 canvas()->setPaintAttribute(QwtPlotCanvas::PaintPacked, false);

#ifdef Q_WS_X11
 canvas()->setAttribute(Qt::WA_PaintOnScreen, true); 
#endif
 alignScales();

 desired= accuracy= desired_min= desired_max= 0;
 w_level = new QwtPlotCurve(QString::fromLocal8Bit("уровень")); 
 w_level->attach(this);
 w_level->setPen(QPen(Qt::blue));  
 w_level->setRawData(d_x, d_y, PLOT_SIZE); 
 reset_diagram();
 f.setPointSize (12);
 setAxisFont(QwtPlot::xBottom, f);
 setAxisFont(QwtPlot::yLeft, f);
 setAxisTitle(QwtPlot::xBottom, QString::fromLocal8Bit("Время,с"));
 setAxisTitle(QwtPlot::yLeft, QString::fromLocal8Bit("Температура,С")); 

 setAxisScale(QwtPlot::xBottom, 0, (SCHEDULE_TXCONTROL_TM * VISUAL_STEP * PLOT_SIZE)/1000);
 setAxisScale(QwtPlot::yLeft, 0, 150);
 // grid 
 QwtPlotGrid *grid = new QwtPlotGrid;
 const QwtScaleDiv *sdx = axisScaleDiv(xBottom);
 const QwtScaleDiv *sdy = axisScaleDiv(yLeft);
 grid->enableX(true);
 grid->enableY(true);
 grid->setXDiv(*sdx);
 grid->setYDiv(*sdy);
 grid->setMajPen(QPen(Qt::darkGray, 0, Qt::DotLine));
 grid->setMinPen(QPen(Qt::gray,  0, Qt::DotLine));
 grid->attach(this);
#if 1
 QwtPlotCurve *desired_w = new QwtPlotCurve(QString::fromLocal8Bit("уставка")); 

 desired_w->attach(this);
 desired_w->setPen(QPen(Qt::darkBlue));  
 desired_w->setRawData(d_x, m0, PLOT_SIZE); 

#endif
#if 0
 //  ...a horizontal line at y = 0...
 m0 = new QwtPlotMarker();
 m1 = new QwtPlotMarker();
 m2 = new QwtPlotMarker();
 m0->setLabel(QString::fromLocal8Bit("уставка"));
 m0->setLabelAlignment(Qt::AlignRight|Qt::AlignTop);
 m0->setLineStyle(QwtPlotMarker::HLine);
 m0->setLinePen(QPen(Qt::darkBlue));
 m0->setYValue(200.0);
 m0->attach(this);
 m1->setLabel(QString::fromLocal8Bit("допуск \"-\""));
 m1->setLabelAlignment(Qt::AlignRight|Qt::AlignTop);
 m1->setLineStyle(QwtPlotMarker::HLine);
 m1->setLinePen(QPen(Qt::darkGreen));
 m1->setYValue(150.0);
 m1->attach(this);
 m2 = new QwtPlotMarker();
 m2->setLabel(QString::fromLocal8Bit("допуск \"+\""));
 m2->setLabelAlignment(Qt::AlignRight|Qt::AlignTop);
 m2->setLineStyle(QwtPlotMarker::HLine);
 m2->setLinePen(QPen(Qt::darkGreen));
 m2->setYValue(250.0);
 m2->attach(this);
#endif

#if 0
    d_zoomer[0] = new Zoomer( QwtPlot::xBottom, QwtPlot::yLeft, canvas());
    d_zoomer[0]->setRubberBand(QwtPicker::RectRubberBand);
    d_zoomer[0]->setRubberBandPen(QColor(Qt::green));
    d_zoomer[0]->setTrackerMode(QwtPicker::ActiveOnly);
    d_zoomer[0]->setTrackerPen(QColor(Qt::white));
    d_zoomer[1] = new Zoomer(QwtPlot::xBottom, QwtPlot::yLeft, canvas());
#endif
    d_panner = new QwtPlotPanner(canvas());
    d_panner->setMouseButton(Qt::MidButton);

    d_picker = new QwtPlotPicker(QwtPlot::xBottom, QwtPlot::yLeft, QwtPicker::PointSelection | QwtPicker::DragSelection, QwtPlotPicker::CrossRubberBand, QwtPicker::AlwaysOn, canvas());
    d_picker->setRubberBandPen(QColor(Qt::green));
    d_picker->setRubberBand(QwtPicker::CrossRubberBand);
    d_picker->setTrackerPen(QColor(Qt::white));

 mutex_0.unlock();
}
/*====================================================================================================================*/

/*====================================================================================================================*/
void DataPlot::reset_diagram(void )
{for (int i = 0; i< PLOT_SIZE; i++)
    {d_x[i] = (SCHEDULE_TXCONTROL_TM * VISUAL_STEP * i)/1000;    
     d_y[i] = 0;
     m0[i]  = m1[i]= m2[i]= 0;
    }
 up_tm_holded=0; progress_tm= 0;
 cntrl_err= signal_amplitude= signal_period= 0;
 w_level->set_visible_size(0); 
 return;
}
/*====================================================================================================================*/
void DataPlot::enableZoomMode(bool on)
{d_panner->setEnabled(on);
#if 0
 d_zoomer[0]->setEnabled(on);
 d_zoomer[0]->zoom(0);
 d_zoomer[1]->setEnabled(on);
 d_zoomer[1]->zoom(0);
#endif
 d_picker->setEnabled(!on);
}

/*====================================================================================================================*/
/* Set a plain canvas frame and align the scales to it */
void DataPlot::alignScales()
{mutex_0.lock();
 canvas()->setFrameStyle(QFrame::Box | QFrame::Plain );
 canvas()->setLineWidth(1);
 for ( int i = 0; i < QwtPlot::axisCnt; i++ )
    {QwtScaleWidget *scaleWidget = (QwtScaleWidget *)axisWidget(i);
     if ( scaleWidget )
        scaleWidget->setMargin(0);
    QwtScaleDraw *scaleDraw = (QwtScaleDraw *)axisScaleDraw(i);
    if ( scaleDraw )
        scaleDraw->enableComponent(QwtAbstractScaleDraw::Backbone, false);
    }
 mutex_0.unlock();
}
/*====================================================================================================================*/
void DataPlot::view_wlevel_diagramm(float v, int control) /* Generate new values  */
{int i;
 /*char s[256];
 sprintf(s, "%s> [%d] v= %u", __FUNCTION__, __LINE__, v);
 qDebug() << s;*/
 mutex_0.lock();
 if(control && !progress_tm)
	{for (int i = 0; i< PLOT_SIZE; i++)
		{d_y[i] = 0;}
	 up_tm_holded=0; 
	 cntrl_err= signal_amplitude= signal_period= 0;
	}
 d_y[progress_tm] = v;	
 if(progress_tm >= (PLOT_SIZE -1))	
	{for (i = 0; i < PLOT_SIZE- 1; i++ )
		d_y[i] = d_y[i+1];
	}
 else
	progress_tm++;
 if(!control)
	progress_tm= 0;
 w_level->set_visible_size(progress_tm); 
 replot();   
 mutex_0.unlock();
}
/*====================================================================================================================*/
void DataPlot::view_desired(int desired_v) /* заданное значение величины */
{int i;
 mutex_0.lock();
 desired= desired_v;
 accuracy= 10.0;
#if 1
for (i = 0; i< PLOT_SIZE; i++)
    {m0[i]= desired;}
#endif
/* m1->setYValue((float)(desired - accuracy));
 m2->setYValue((float)(desired + accuracy));*/
 replot();   
 mutex_0.unlock();
}
/*====================================================================================================================*/
int DataPlot::get_cntrl_up_tm(void)                   /* измеряем время выхода на уставку */
{int i;
 if(!up_tm_holded)
	for (i = 0; i < (progress_tm -1); i++)
		{if(((int)d_y[i]) >= desired)                /* пока измеряемая величина не будет больше (уставки-допуск) */
			return (up_tm_holded= i);
		}
 return up_tm_holded;
}
/*====================================================================================================================*/
int DataPlot::scan_extremp(int from)           		/* находим верхнюю точку экстремума  */
{
    int t, h;
    for (t = from; t < (progress_tm - 5); t++) {
        h = d_y[t+2];
        if ((d_y[t] < h) && (d_y[t+1] <= h) && (d_y[t+3] <= h) && (d_y[t+4] <= h) && (h > desired_min)) {
            if(t < 10)
                return 0;
            return (t+2);
		}
    }

    return 0;
}
/*====================================================================================================================*/
int DataPlot::scan_extremn(int from)           		 							/* находим верхнюю точку экстремума  */
{int t, h;
 for (t = from; t < (progress_tm -5); t++)
    {h= d_y[t+2];
	 if( (d_y[t] > h) && (d_y[t+1] >= h) && (d_y[t+3] >= h) && (d_y[t+4] >= h) && (h < desired_max)) 
		{if(t < 10)
			return 0;
		 return (t+2);
		}
    }
 return 0;
}
/*====================================================================================================================*/
int DataPlot::get_signal_period(void)            /* измеряем период колебаний */
{int i, tm;
 if(!(i= scan_extremp(0)))
	return 0;
 if(!(i= scan_extremp(i+ 5)))
	return 0;
 if(!(tm= scan_extremp(i+ 5)))
	return 0;
 if((tm- i) > 5)	
    signal_period= tm - i;
 return signal_period;
}
/*====================================================================================================================*/
int DataPlot::get_signal_amplitude(void)              /* измеряем амплитуду колебаний сигнала */
{int i, j, v;
/* if(!(i= scan_extremp(0)))
	return 0;*/
 if((i= scan_extremp(0/*i+ 5*/)) != 0)
    if((j= scan_extremn(i+ 5)) != 0)
        {v= (d_y[i] - d_y[j])/2;
         if(signal_amplitude < v)
            signal_amplitude= v;
        }
 return signal_amplitude;
}
/*====================================================================================================================*/
int DataPlot::get_cntrl_err(void)           /* измеряем ошибку регулирования */
{
    int i, v;

    if (!(i = scan_extremp(0)))
        return 0;
	
 for (; i < (progress_tm -1); i++)  
    {v= ((int)d_y[i]) - desired;
	 if(v < 0) 
		v= -v;
     if(v > cntrl_err)
        cntrl_err= v;
    }
 return cntrl_err;
}
/*====================================================================================================================*/
DataPlot::~DataPlot()
{

}
