#ifndef WINDOW_H
#define WINDOW_H

#include <qwt/qwt_thermo.h>
#include <qwt/qwt_knob.h>
#include <qwt/qwt_plot.h>
#include <qwt/qwt_plot_curve.h>

#include <QBoxLayout>
#include "adcreader.h"
#include "circularbuffer.h"

//set length of the ringbuffer to be 50
//#define BUFFER_LENGTH 128

// class definition 'Window', inheritance of QWidget
class Window : public QWidget
{
	// must include the Q_OBJECT macro for for the Qt signals/slots framework to work with this class
	Q_OBJECT

public:
	Window(); // default constructor - called when a Window is declared without arguments. Must be the same name as the class name.

	~Window(); //deconstructor

	void timerEvent( QTimerEvent * );// pointers and references

public slots:
	void setGain(double gain);
	

public:
	//	double ringBuffer[BUFFER_LENGTH];
	//	int buffer_index;
	//channel numbers
	//	int tempChannel;
	//	int humChannel;
	//	int lightChannel;

	//sensor buffers
	
	Circularbuffer tempbuffer;
	Circularbuffer humbuffer;
	Circularbuffer lightbuffer;


// internal variables for the window class
private:
	QwtKnob      *knob;
	QwtThermo    *thermo;
	QwtPlot      *plot;
	QwtPlotCurve *curve;
	QwtPlotCurve *curve2;

	// layout elements from Qt itself http://qt-project.org/doc/qt-4.8/classes.html
	QVBoxLayout  *vLayout;  // vertical layout
	QHBoxLayout  *hLayout;  // horizontal layout

	static const int plotDataSize = 100;

	// data arrays for the plot
	double xData[plotDataSize];
	double yData[plotDataSize];
	double y2Data[plotDataSize];

	double gain;
	int count;

	ADCreader *adcreader;
};

#endif // WINDOW_H
