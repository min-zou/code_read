
class rock_driver
{
public:
    enum {
        DEFAULT_TIMEOUT = 2000, //2000 ms
    };

    enum {
        DRIVER_TYPE_SERIALPORT = 0x0,
    };

public:
    static rock_driver *CreateDriver(uint32_t drivertype = DRIVER_TYPE_SERIALPORT);
    static void DisposeDriver(rock_driver * drv);

public:
    virtual int32_t connect(const char * port_path, uint32_t baudrate, uint32_t flag = 0)=0;
    virtual void disconnect()=0;
    virtual bool isConnected()=0;
    virtual int32_t sendcmd(int16_t left, int16_t right)=0;
    virtual int32_t sendstop()=0;
    virtual int32_t getenc(int32_t *encbuffer,uint32_t timeout = DEFAULT_TIMEOUT)=0;
    virtual int32_t start()=0;
    virtual int32_t setpid(uint8_t kp, uint8_t ki, uint8_t kd)=0;

protected:
    virtual uint8_t checksum(uint8_t *buffer)=0;
    rock_driver() {}
    virtual ~rock_driver() {}
};
