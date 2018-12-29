#include "rock_driver.h"

class rock_driver_serialimpl:public rock_driver
{
public:
    rock_driver_serialimpl();
    virtual ~rock_driver_serialimpl();

public:
    virtual int32_t connect(const char * port_path, uint32_t baudrate, uint32_t flag = 0);
    virtual void disconnect();
    virtual bool isConnected();
    virtual int32_t sendcmd(int16_t left, int16_t right);
    virtual int32_t sendstop();
    virtual int32_t getenc(int32_t *encbuffer,uint32_t timeout = DEFAULT_TIMEOUT);
    virtual int32_t start();
    virtual int32_t setpid(uint8_t kp, uint8_t ki, uint8_t kd);


protected:
    virtual uint8_t checksum(uint8_t *buffer);
    bool  _isConnected;
    rock_rxtx * _rxtx;
};
