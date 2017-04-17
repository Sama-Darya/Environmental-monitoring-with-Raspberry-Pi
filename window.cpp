#include "window.h"
#include "adcreader.h"
#include "circularbuffer.h"



//#include <cmath>  // for sine stuff

//sensor buffers, need to be accessable to window.cpp so put extern in front
extern Circularbuffer tempbuffer;	
extern Circularbuffer humbuffer;
extern Circularbuffer lightbuffer;

Window::Window() : gain(5), count(0)
{

	knob = new QwtKnob;
	// set up the gain knob
	knob->setValue(gain);

	// use the Qt signals/slots framework to update the gain -
	// every time the knob is moved, the setGain function will be called
	connect( knob, SIGNAL(valueChanged(double)), SLOT(setGain(double)) );

	// set up the thermometer
	thermo = new QwtThermo; 
	thermo->setFillBrush( QBrush(Qt::blue) );
	thermo->setRange(0, 30);
	thermo->show();

	/*
	// set up the initial plot data
	for( int index=0; index<plotDataSize; ++index )
	{
		xData[index] = index;
		yData[index] = gain * sin( M_PI * index/50 );
		//yData[index] = read_voltage(0x68,2, 12, 1,1);
	}
	*/

	curve = new QwtPlotCurve;
	curve2= new QwtPlotCurve;
	plot = new QwtPlot;
	// make a plot curve from the data and attach it to the plot
	curve->setSamples(xData, yData, plotDataSize);
	curve->setSamples(xData, y2Data, plotDataSize);
	curve->attach(plot);
	curve2->attach(plot);

	plot->replot();
	plot->show();


	// set up the layout - knob above thermometer
	vLayout = new QVBoxLayout;
	vLayout->addWidget(knob);
	vLayout->addWidget(thermo);

	// plot to the left of knob and thermometer
	hLayout = new QHBoxLayout;
	hLayout->addLayout(vLayout);
	hLayout->addWidget(plot);
	
	setLayout(hLayout);
	/*
	hLayoutTemp = new QHBoxLayout;
	hLayoutTemp->addLayout(vLayoutTemp);
	hLayoutTemp->addWidget(plot);
	setLayout(hLayoutTemp);
	*/

	// This is a demo for a thread which can be
	// used to read from the ADC asynchronously.
	// At the moment it doesn't do anything else than
	// running in an endless loop and which prints out "tick"
	// every second.
	adcreader = new ADCreader();
	//read initial data from temperature sensor
	
	//initial fill half of the buffer
	for(int index=0; index<(plotDataSize); ++index){
	  //xData[index] = index;
	       if(!tempbuffer.Full())
		 tempbuffer.Insert((adcreader->read_voltage(0x68,2, 12, 1,1) - 0.621)/0.01);
	       if(!humbuffer.Full())
		 humbuffer.Insert((0.826-(adcreader->read_voltage(0x68,3, 12, 1,1)))/0.04);
		 }
	
	//data required for plotting
	for(int index=0; index<plotDataSize; ++index){
	       xData[index] = index;
	       // yData[index] = (adcreader->read_voltage(0x68,2, 12, 1,1) - 0.621)/0.01;
	       //y2Data[index] = (0.826-(adcreader->read_voltage(0x68,3, 12, 1,1)))/0.04;
	       
	       if(!tempbuffer.Empty())
		 yData[index] = tempbuffer.Remove();
	       if(!humbuffer.Empty())
		 y2Data[index] = humbuffer.Remove();
	       
	}
	
	adcreader->start();
	//adcreader->run(); //trying to print
}

Window::~Window() {
	// tells the thread to no longer run its endless loop
	adcreader->quit();
	// wait until the run method has terminated,
    //to block the calling thread, until the other thread has finished execution: use wait();
	adcreader->wait();
	delete adcreader;
}

void Window::timerEvent( QTimerEvent * )
{
  //double inVal = gain * sin( M_PI * count/50.0 );
  //double temp_volt,light_volt,hum, hum_volt, temp;
  // double light_volt = 0.5;
  //temp_volt = adcreader->read_voltage(0x68,2, 12, 1,1);
  //hum_volt = adcreader->read_voltage(0x68,3, 12, 1,1);
  /*
  if(!tempbuffer.Empty())
    temp_volt = tempbuffer.Remove();
  if(!humbuffer.Empty())
    hum_volt = humbuffer.Remove();
  */
  /*
  if(tempbuffer.Full()){ fprintf(stderr,"The Buffer is FULL!\n");}
  if(!tempbuffer.Full()){tempbuffer.Insert((adcreader->read_voltage(0x68,2, 12, 1,1) - 0.621)/0.01);}
  if(!humbuffer.Full()){humbuffer.Insert((0.826-(adcreader->read_voltage(0x68,3, 12, 1,1)))/0.04);}
  */
  //++count;
  // temp = (temp_volt - 0.621)/0.01; //temperature calculation
  //hum = (0.826-hum_volt)/0.04; //where 0.826 is from datasheet and 3.198/75.3=0.04
  
	// add the new input to the plot
	//memmove( yData, yData+1, (plotDataSize-1) * sizeof(double) );
	//yData[plotDataSize-1] = inVal;
        //temperature
	memmove( yData, yData+1, (plotDataSize-1) * sizeof(double) );
	yData[plotDataSize-1] = tempbuffer.Remove();
	//yData[plotDataSize-1] = temp;
	
	//// for humidity
	memmove( y2Data, y2Data+1, (plotDataSize-1) * sizeof(double) );
	y2Data[plotDataSize-1]=humbuffer.Remove();
	//y2Data[plotDataSize-1]=hum;
	//curves
	curve->setSamples(xData, yData, plotDataSize);
	curve2->setSamples(xData, y2Data, plotDataSize);

	// Sama: adding the axis lables
	//plot->setAxisTitle(QwtPlot::yLeft, "Temperature");
	//plot->setAxisTitle(QwtPlot::yRight, "Humidity");
	//plot->setAxisTitle(QwtPlot::xBottom, "Time");

	
	plot->replot();

	// set the thermometer value
	//thermo->setValue( light_volt + 10 );
	thermo->setValue( 10 );
        
}


// this function can be used to change the gain of the A/D internal amplifier
void Window::setGain(double gain)
{
	// for example purposes just change the amplitude of the generated input
	this->gain = gain;
}
