#include "mvtx_file_plugin.h"

#include "parseargument.h"

#include <daq_device_mvtx_file.h>


#include <strings.h>

int mvtx_file_plugin::create_device(deviceblock *db)
{

  //  std::cout << __LINE__ << "  " << __FILE__ << "  " << db->argv0 << "  " << db->npar << std::endl;

  int eventtype;
  int subid;

  if ( strcasecmp(db->argv0,"device_mvtx_file") == 0 ) 
    {
      // we need at least 2 params
      if ( db->npar <3 ) return 1; // indicate wrong params
      
      eventtype  = get_value ( db->argv1); // event type
      subid = get_value ( db->argv2); // subevent id

      if ( db->npar == 3)
	{
	  add_readoutdevice ( new daq_device_mvtx_file( eventtype,
						  subid ));
	  return 0;  // say "we handled this request" 
	}

      else if ( db->npar == 4)
	{
	  int trigger = get_value ( db->argv3);

	  add_readoutdevice ( new daq_device_mvtx_file( eventtype,
						  subid,
						  trigger ));
	  return 0;  // say "we handled this request" 
	}

      else if ( db->npar == 5)
	{
	  int trigger = get_value ( db->argv3);
	  int nunits = get_value ( db->argv4);

	  add_readoutdevice ( new daq_device_mvtx_file( eventtype,
						  subid,
						  trigger,
						  nunits));
	  return 0;  // say "we handled this request" 
	}

      else if ( db->npar == 6)
	{
	  int trigger = get_value ( db->argv3);
	  int nunits = get_value ( db->argv4);
	  int npackets = get_value ( db->argv5);

	  add_readoutdevice ( new daq_device_mvtx_file( eventtype,
						  subid,
						  trigger,
						  nunits,
						  npackets));
	  return 0;  // say "we handled this request" 
	}

      else
	{
	  return 1; // say it is our device but the parameters are wrong 
	}
    } 


  return -1; // say " this is not our device"

}

void mvtx_file_plugin::identify(std::ostream& os, const int flag) const
{

  if ( flag <=2 )
    {
      os << " - DAM Plugin" << std::endl;
    }
  else
    {
      os << " - DAM Plugin, provides - " << std::endl;
      os << " -     device_mvtx_file (evttype, subid [, npackets, trigger] ) - DAM FELIX Board " << std::endl;
    }
      

}


mvtx_file_plugin _mvtx_filep;
