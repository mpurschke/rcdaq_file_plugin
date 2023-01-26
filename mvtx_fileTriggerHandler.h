#ifndef __MVTX_FILETRIGGERHANDLER_H__
#define __MVTX_FILETRIGGERHANDLER_H__

#include "TriggerHandler.h"


class mvtx_fileTriggerHandler : public TriggerHandler {

public:

  mvtx_fileTriggerHandler(const int etype)
    {
      _etype = etype;
      _poll_count = 0;
    };

  ~mvtx_fileTriggerHandler() {};

  int set_mvtx_filefd ( const int mvtx_file_fd);
  //  int set_selftrigger(const int sleepinterval) { _self_trigger = sleepinterval;};

  int enable();

  // this is the virtual worker routine
  int wait_for_trigger( const int moreinfo=0);

 protected:
  
  int _mvtx_file_fd;
  int _etype;
  int _poll_count;
};

#endif
