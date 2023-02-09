
#include <iostream>

#include <daq_device_mvtx_file.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdint.h>
#include <fcntl.h>

#define DATA_LENGTH          256*128 

using namespace std;

int readn (int fd, char *ptr, const int nbytes);


daq_device_mvtx_file::daq_device_mvtx_file(const int eventtype
			       , const int subeventid
			       , const int trigger
			       )
{

  m_eventType  = eventtype;
  m_subeventid = subeventid;

  _trigger = trigger;
  _broken = 0;

  if ( _trigger )
    {
      //  cout << __LINE__ << "  " << __FILE__ << " registering triggerhandler " << endl;
      _th  = new mvtx_fileTriggerHandler (m_eventType);
      
      registerTriggerHandler ( _th);

    }
  else
    {
      _th = 0;
    }

  _length =  DATA_LENGTH;   // we try this. just one event
  
}

daq_device_mvtx_file::~daq_device_mvtx_file()
{

  if (_th)
    {
      clearTriggerHandler();
      delete _th;
      _th = 0;
    }
}


int  daq_device_mvtx_file::init()
{

  if ( _broken ) 
    {
      //      cout << __LINE__ << "  " << __FILE__ << " broken ";
      //      identify();
      return 0; //  we had a catastrophic failure
    }

  _broken = 0;

  _mvtx_file_fd = open("THEFILE", O_RDONLY);

  if ( _mvtx_file_fd < 0)
    {
      _broken = 1;
      return -1;
    }

  
  if ( _trigger )
    {
      _th->set_mvtx_filefd( _mvtx_file_fd);
    }

  return 0;

}

// the put_data function

int daq_device_mvtx_file::put_data(const int etype, int * adr, const int length )
{

  if ( _broken ) 
    {
      cout << __LINE__ << "  " << __FILE__ << " broken ";
      //      identify();
      return 0; //  we had a catastrophic failure
    }

  //  cout << __LINE__ << "  " << __FILE__ << " starting put_data "  << endl;



  int len = 0;

  if (etype != m_eventType )  // not our id
    {
      return 0;
    }


  subevtdata_ptr sevt =  (subevtdata_ptr) adr;
  // set the initial subevent length
  sevt->sub_length =  SEVTHEADERLENGTH;

  // update id's etc
  sevt->sub_id = m_subeventid;
  sevt->sub_type=4;
  sevt->sub_decoding = 105;  //IDMVTXV2
  sevt->reserved[0] = 0;
  sevt->reserved[1] = 0;

  
  unsigned char *dest = (unsigned char *) &sevt->data;

  int ret;

  int go_on = 1;
  int count = 0;

  while ( go_on && count < DATA_LENGTH -32)
    {

      ret = read(_mvtx_file_fd, dest, 32);
      if (ret < 32 )
	{
	  go_on = 0;
	  break;
	}
      cout << setw(10) << count << ": " << hex;
      for ( int k = 0; k < 3; k++)
	{
	  for ( int i  = 0; i< 10; i++) cout << setw(3)  << (uint16_t) dest[10*k +i];
	  cout << " ";
	}
      cout << " " << setw(3) <<  (uint16_t) dest[30] << setw(3) <<  (uint16_t) dest[31] << dec << endl;

      if ( dest[31] == 0xab && count > 0)
	{
	  lseek ( _mvtx_file_fd, -32, SEEK_CUR);
	  go_on = 0;
	  break;
	}
      
      count += ret;
      dest += ret;
    }
  //cout << __LINE__ << "  " << __FILE__ << " read  "  << ret << " words " << endl;

  //      sevt->sub_padding = ret%2 ;
  sevt->sub_padding = 0;  // we can never have an odd number of uint16s
  
  sevt->sub_length += (count/4 + sevt->sub_padding);
  cout << __LINE__ << "  " << __FILE__ << " returning "  << sevt->sub_length << endl;

  return sevt->sub_length;
}

  
void daq_device_mvtx_file::identify(std::ostream& os) const
{
  if ( _broken) 
    {
      os << "MVTX converter  Event Type: " << m_eventType 
	 << " Subevent id: " << m_subeventid
	 << " ** not functional ** " << _broken << endl;
    }
  else
    {
      os << "MVTX converter  Event Type: " << m_eventType 
	 << " Subevent id: " << m_subeventid; 
      if (_trigger) os << " *Trigger*" ;
      os << endl;

    }
}

int daq_device_mvtx_file::max_length(const int etype) const
{
  if (etype != m_eventType) return 0;
  return  ( DATA_LENGTH );

}


// the rearm() function
int  daq_device_mvtx_file::rearm(const int etype)
{
  return 0;
}

int daq_device_mvtx_file::endrun() 
{
  
  close (_mvtx_file_fd);
  
  return 0;
}


