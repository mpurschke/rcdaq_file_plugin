
#include "mvtx_fileTriggerHandler.h"


#include <iostream>
#include <iomanip>
#include <sys/types.h>
#include <stdint.h>

#include <unistd.h>
#include <fcntl.h>

#define DATA_LENGTH          137*256 // 137 words * 256 channels
#define FEE_SAMPA_CTRL       0x5
#define DAM_DMA_FIFO         0x5
#define DAM_DMA_CTRL         0x4004
#define DAM_DMA_BURST_LENGTH 0x4002
#define DAM_DMA_WRITE_PTR    0x4003

//#include "pl_lib.h"

using namespace std;

int mvtx_fileTriggerHandler::enable()
{
  cout << __FILE__ << " " << __LINE__ << " enabling DAQ trigger" << endl;
    
  // Disable DMA engine
  //  pl_register_write(_mvtx_file_fd, DAM_DMA_CTRL, 0x0);
  
  // Reset FEE FIFOs
  //pl_register_write(_mvtx_file_fd, 0x24, 0xf);
  
  //mvtx_file_reset_dma_engine(_mvtx_file_fd);
  
  // Set burst length
  //pl_register_write(_mvtx_file_fd, DAM_DMA_BURST_LENGTH, DATA_LENGTH);
  //size_t len = pl_register_read(_mvtx_file_fd, DAM_DMA_BURST_LENGTH);
  
  // Enable DMA engine
  //pl_register_write(_mvtx_file_fd, DAM_DMA_CTRL, 1 << 3 | 1 << 1);


  // Take FEE FIFOs out of reset
  //pl_register_write(_mvtx_file_fd, 0x24, 0x0);
  return 0;
}


int mvtx_fileTriggerHandler::wait_for_trigger( const int moreinfo)
{

  // fd_set read_flags;
  // struct timeval timeout;
  // int sel;

  // timeout.tv_sec = 4;
  // timeout.tv_usec = 0;
  // FD_ZERO(&read_flags);
  // FD_SET(_mvtx_file_fd, &read_flags);

  // sel = select(_mvtx_file_fd+1, &read_flags, NULL, (fd_set*)0, &timeout);
  // if (sel < 0)
  //   {
  //     perror("select()");
  //   }

  // _poll_count++;
  
  // if (FD_ISSET(_mvtx_file_fd, &read_flags))
  //   {
  //     //      cout << __LINE__ << "  " << __FILE__ << " trigger after " << _poll_count << " polls" << endl;
  //     _poll_count = 0;
      return _etype;
      //    }
  
      //  return 0;

}

int mvtx_fileTriggerHandler::set_mvtx_filefd( const int mvtx_file_fd)
{
  _mvtx_file_fd = mvtx_file_fd;
  return 0;
}
