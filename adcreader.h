/*  adcreader.h
*   Reads from the MCP3424 ADC on the ADC Differential Pi and Delta-Sigma Pi.
*   Two functions are available to use.
*   read_raw(address,channel,bitrate,pga,conversionmode) returns the raw number from the ADC
*   read_voltage(address,channel,bitrate,pga,conversionmode) returns the voltage present at the ADC input
*   Required package{
*   apt-get install libi2c-dev
*/
#ifndef ADCREADER
#define ADCREADER

#include <QThread>

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <assert.h>

#include "circularbuffer.h"
#define readwrite_buff 10


//class declaration
class ADCreader : public QThread
{
public:
    //variables declaration or instance variable
    //static int i2cbus;
    //const char *fileName = "/dev/i2c-1"; // change to /dev/i2c-0 if you are using a revision 0002 or 0003 model B
  // unsigned char writebuffer[10] = { 0 };
  //unsigned char readbuffer[10] = { 0 };
  //static char signbit = 0;
  
   int i2cbus;
   //const char *fileName;
  unsigned char writebuffer[readwrite_buff];
  unsigned char readbuffer[readwrite_buff];
  char signbit;


  
    
    //functions or function prototypes
  ADCreader(void) {running = 0;}; //constructor
	void quit(void);
	void run(void);
    /// <summary>
    /// Reads the raw value from the selected ADC channel
    /// </summary>
    /// <param name="address">I2C Address e.g.  0x68</param>
    /// <param name="channel">1 to 4</param>
    /// <param name="bitrate">12, 14, 16 or 18</param>
    /// <param name="pga">1, 2, 4 or 8</param>
    /// <param name="conversionmode">0 = one shot conversion, 1 = continuous conversion</param>
    /// <returns>raw long value from ADC buffer</returns>
    int read_raw(char address, char channel, int bitrate, int pga,	char conversionmode);
    
    
    /// <summary>
    /// Returns the voltage from the selected ADC channel
    /// </summary>
    /// <param name="address">I2C Address e.g.  0x68</param>
    /// <param name="channel">1 to 4</param>
    /// <param name="bitrate">12, 14, 16 or 18</param>
    /// <param name="pga">1, 2, 4 or 8</param>
    /// <param name="conversionmode">0 = one shot conversion, 1 = continuous conversion</param>
    /// <returns>double voltage value from ADC</returns>
    double read_voltage(char address, char channel, int bitrate, int pga, char conversionmode);
private:
    //variables declaration or instance variable
	bool running;
    
    //functions or function prototypes
     void read_byte_array(char address, char reg, char length);
     char update_byte(char byte, char bit, char value);
     char set_pga(char config, char gain);
     char set_bit_rate(char config, char rate);
     char set_conversion_mode(char config, char mode);
     char set_channel(char config, char channel);

};

#endif
