#ifndef WIRE_H
#define WIRE_H

#include <cstdlib>
#include <cstdint>

size_t const TRANSMIT_BUF_SIZE = 16;
size_t const RECV_BUF_SIZE = 16;

class TwoWire
{
  private:
    int fd;
    uint8_t address;

    uint8_t transmitBuf[TRANSMIT_BUF_SIZE];
    uint8_t* writePos;
    uint8_t recvBuf[RECV_BUF_SIZE];
    ssize_t recvBufLen;
    uint8_t* readPos;

  public:
    TwoWire();
    virtual ~TwoWire();

    void begin();
    void begin(uint8_t address);
    void beginTransmission(uint8_t);
    virtual size_t write(uint8_t);
    virtual int read(void);
    uint8_t endTransmission(void);
    uint8_t requestFrom(uint8_t address, uint8_t quantity);
    int available(void);
};

extern TwoWire Wire;

#endif /* WIRE_H */
