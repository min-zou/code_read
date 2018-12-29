#include <stdio.h> 
#include <string.h> 
#include <unistd.h>
#include <fcntl.h>
#include <errno.h> 
#include <termios.h>
#include <stdlib.h>  
#include <assert.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "rock_rxtx.h"
class rock_serial : public rock_rxtx
{
    public:
	rock_serial();
	virtual ~rock_serial();
	virtual bool bind(const char * portname, uint32_t baudrate, uint32_t flags = 0);
	virtual bool open();
	virtual void close();
	virtual void flush(uint32_t flags);

    virtual int waitfordata(size_t data_count,uint32_t timeout = -1, size_t * returned_size = NULL);

	virtual int senddata(const unsigned char * data, size_t size);
	virtual int recvdata(unsigned char * data, size_t size);

        virtual int waitforsent(uint32_t timeout = -1, size_t * returned_size = NULL);
        virtual int waitforrecv(uint32_t timeout = -1, size_t * returned_size = NULL);

        virtual size_t rxqueue_count();

	virtual uint32_t getTermBaudBitmap(uint32_t baud);

protected:
	bool open(const char * portname, uint32_t baudrate, uint32_t flags = 0);
	void _init();
	char _portName[200];
    	uint32_t _baudrate;
    	uint32_t _flags;
    	int serial_fd;
        size_t required_tx_cnt;
        size_t required_rx_cnt;
};
