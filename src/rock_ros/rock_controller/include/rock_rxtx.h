#include <stdint.h>
#include <stddef.h>
class rock_rxtx
{
public:
    enum{
        ANS_OK      = 0,
        ANS_TIMEOUT = -1,
        ANS_DEV_ERR = -2,
    };

    static rock_rxtx * CreateRxTx();
    static void ReleaseRxTx( rock_rxtx * );

    rock_rxtx():_is_serial_opened(false){}
    virtual ~rock_rxtx(){}

    virtual void flush( uint32_t flags) = 0;

    virtual bool bind(const char * portname, uint32_t baudrate, uint32_t flags = 0) = 0;
    virtual bool open() = 0;
    virtual void close()  = 0;

    virtual int waitfordata(size_t data_count,uint32_t timeout = -1, size_t * returned_size = NULL) = 0;

    virtual int senddata(const unsigned char * data, size_t size) = 0;

    virtual int recvdata(unsigned char * data, size_t size) = 0;

    virtual int waitforsent(uint32_t timeout = -1, size_t * returned_size = NULL) = 0;
    virtual int waitforrecv(uint32_t timeout = -1, size_t * returned_size = NULL) = 0;

    virtual size_t rxqueue_count() = 0;

    virtual bool isOpened()
    {
        return _is_serial_opened;
    }

protected:

    volatile bool   _is_serial_opened;
};
