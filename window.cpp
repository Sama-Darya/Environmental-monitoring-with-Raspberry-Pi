//Add header files
#include "window.h"
#include "adcreader.h"
#include "circularbuffer.h"



//sensor buffers, need to be accessable to window.cpp so put extern in front
extern Circularbuffer tempbuffer;	
extern Circularbuffer humbuffer;
extern Circularbuffer lightbuffer;

Window::Window() :gain(5), count(0), currentmode(true)

{

  tBtn=new QPushButton();
  tBtn->setText("Display Realtive Humidity");
  tBtn->resize(500,1500);
  connect( tBtn, SIGNAL(pressed()), SLOT(modetoggle()) );

  tlabel= new QLabel;
  tlabel->setText("Light level");
  
	// set up the thermometer
  thermo = new QwtThermo; 
	thermo->setFillBrush( QBrush(Qt::blue) );
	thermo->setRange(0, 100);
	thermo->show();;
  
	curve = new QwtPlotCurve;
	curve2= new QwtPlotCurve;
	plot = new QwtPlot;


	curve->setSamples(xData, yData, plotDataSize);
	curve2->setSamples(xData, y2Data, plotDataSize);

	plot->show();
	
       hhLayout= new QHBoxLayout;
       hhLayout->addWidget(tlabel);
       hhLayout->addWidget(thermo);
	

	vLayout = new QVBoxLayout;
       	vLayout->addWidget(tBtn);
	vLayout->addLayout(hhLayout);


	hLayout = new QHBoxLayout;
	hLayout->addLayout(vLayout);
	hLayout->addWidget(plot);
	
	setLayout(hLayout);

	adcreader = new ADCreader();
	//read initial data from temperature sensor
	
	//fill buffer for initial plotting
	for(int index=0; index<plotDataSize; ++index){
	       if(!tempbuffer.Full())
		 tempbuffer.Insert((adcreader->read_voltage(0x68,2, 12, 1,1) - 0.621)/0.01);
	       if(!humbuffer.Full())
		 humbuffer.Insert((0.826-(adcreader->read_voltage(0x68,3, 12, 1,1)))/0.04);
	       if(!lightbuffer.Full()){lightbuffer.Insert((adcreader->read_voltage(0x68,1, 12, 1,1)/1.98)*100);}
	     
	 }
	
	//data required for plotting
	for(int index=0; index<plotDataSize; ++index){
	       xData[index] = index;     
	       if(!tempbuffer.Empty()){yData[index] = tempbuffer.Remove();}
	       if(!humbuffer.Empty()){y2Data[index] = humbuffer.Remove();}   
	}
	
	adcreader->start();
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
   
  if(!lightbuffer.Empty()){thermo->setValue(lightbuffer.Remove());}
  
	memmove( yData, yData+1, (plotDataSize-1) * sizeof(double) );
      	yData[plotDataSize-1] = tempbuffer.Remove();

	memmove( y2Data, y2Data+1, (plotDataSize-1) * sizeof(double) );
	y2Data[plotDataSize-1]=humbuffer.Remove();

	memmove( y3Data, y3Data+1, (plotDataSize-1) * sizeof(double) );
	y3Data[plotDataSize-1]=lightbuffer.Remove();

	curve->setSamples(xData, yData, plotDataSize);
	curve2->setSamples(xData, y2Data, plotDataSize);

	plot->setTitle("Scalable Environmental Monitoring System ");
	
        
	plot->setAxisTitle(QwtPlot::xBottom, "Time");

	if (currentmode==true)
{
        curve2->detach();
       	curve->attach(plot);
       	plot->replot();
	plot->setAxisTitle(QwtPlot::yLeft, "Temperature (deg. C)");
	tBtn->setText("Display Realtive Humidity");

 }else{
	curve->detach(); 
       	curve2->attach(plot);
	plot->replot();
	plot->setAxisTitle(QwtPlot::yLeft, "Relative Humidity (%)");
	tBtn->setText("Display Temperature");
	}
	  
        
}
// this function can be used to change the gain of the A/D internal amplifier
void Window::setGain(double gain)
{
	// for example purposes just change the amplitude of the generated input
	this->gain = gain;
}

void Window::modetoggle()
{

    currentmode = !currentmode;
    if (currentmode == false){
	
    }
    else if (currentmode == true)
    {

    }

}
