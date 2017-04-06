/*
This is the main file running the GUI and other threads- Window Class.
Team 18,
Date: 06 April 2017
Last Modification:
Main changes:
*/

#include <window.h>  // self-defined

#include <QApplication> // library from QT

int main(int argc, char *argv[])  
{
	QApplication app(argc, argv); // count and vector arguments, needed for QT appliocation

	// instantiate an object called window from Window Class
	Window window; // Window class is defined in window.cpp
	window.showMaximized();

	// call the window.timerEvent function every 40 ms
	window.startTimer(40); // refreshes the window every 40ms with new data

	// execute the application
	return app.exec(); 
}
