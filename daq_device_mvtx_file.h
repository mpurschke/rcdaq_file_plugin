#ifndef __DAQ_DEVICE_MVTX_FILE__
#define __DAQ_DEVICE_MVTX_FILE__


#include <daq_device.h>
#include <stdio.h>
#include <mvtx_fileTriggerHandler.h>

//class Fee;

class daq_device_mvtx_file: public  daq_device {


public:

  daq_device_mvtx_file(const int eventtype
		 , const int subeventid
		 , const int trigger = 1);


  ~daq_device_mvtx_file();


  void identify(std::ostream& os = std::cout) const;

  int max_length(const int etype) const;

  // functions to do the work

  int put_data(const int etype, int * adr, const int length);

  int init();

  int rearm( const int etype);
  
  int endrun();

  
 protected:

  int _mvtx_file_fd;
  
  int _broken;

  int _trigger;

  int _length;
  
  mvtx_fileTriggerHandler *_th;


};


#endif
