#ifndef WINDOW_H
#define WINDOW_H

#include <qwt/qwt_thermo.h>
#include <qwt/qwt_knob.h>
#include <qwt/qwt_plot.h>
#include <qwt/qwt_plot_curve.h>

#include <QPushButton>
#include <QLabel>

#include <QBoxLayout>
#include "adcreader.h"
#include "circularbuffer.h"





// class definition 'Window', inheritance of QWidget
class Window : public QWidget
{
	// must include the Q_OBJECT macro for for the Qt signals/slots framework to work with this class
	Q_OBJECT

public:

	
	Window(); // default constructor - called when a Window is declared without arguments. Must be the same name as the class name.

	~Window(); //deconstructor

	void timerEvent( QTimerEvent * );

public slots:
	void setGain(double gain);

	void modetoggle();

private:

    QTimer* myTimer;

	QwtKnob      *knob;
	QwtThermo    *thermo;
	QwtPlot      *plot;
	QwtPlot      *plot2;
	QwtPlotCurve *curve;
	QwtPlotCurve *curve2;
	QPushButton *tBtn;
	QLabel *tlabel;

	// layout elements from Qt itself http://qt-project.org/doc/qt-4.8/classes.html
	QVBoxLayout  *vLayout;  // vertical layout
	QHBoxLayout  *hLayout, *hhLayout;  // horizontal layout


	static const int plotDataSize = 100;

	// data arrays for the plot
	double xData[plotDataSize];
	double yData[plotDataSize];
	double y2Data[plotDataSize];
	double y3Data[plotDataSize];

	double gain;
	int count;

	ADCreader *adcreader;


	bool currentmode;
	
};

#endif // WINDOW_H
