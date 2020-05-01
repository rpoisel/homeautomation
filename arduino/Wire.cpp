#include "Wire.h"

#include <linux/i2c-dev.h>

#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include <cstdint>
#include <cstdlib>
#include <iostream>

static int const FD_INVALID = -1;
static char const* I2C_DEVICE_PATH = "/dev/i2c-1";

TwoWire::TwoWire()
{
  fd = open(I2C_DEVICE_PATH, O_RDWR);
  if (fd == -1)
  {
    std::cerr << "Failed to open I2C bus." << std::endl;
  }
}

TwoWire::~TwoWire()
{
  if (fd < 0)
  {
    return;
  }
  close(fd);
}

void TwoWire::begin() { begin(0); }

void TwoWire::begin(uint8_t address) { (void)address; }

void TwoWire::setClock(uint32_t clock) { (void)clock; }

void TwoWire::beginTransmission(uint8_t address)
{
  if (ioctl(fd, I2C_SLAVE, address) == -1)
  {
    std::cerr << "Cannot set address for output module" << std::endl;
    return;
  }
  writePos = &transmitBuf[0];
}

size_t TwoWire::write(uint8_t value)
{
  if (writePos - &transmitBuf[0] >= sizeof(transmitBuf))
  {
    return 0;
  }
  *writePos = value;
  writePos++;
  return sizeof(value);
}

uint8_t TwoWire::endTransmission(void)
{
  ssize_t numBytes = ::write(fd, transmitBuf, writePos - transmitBuf);
  return numBytes > 0 ? 0 : 4;
}

uint8_t TwoWire::requestFrom(uint8_t address, uint8_t quantity)
{
  recvBufLen = 0;
  if (ioctl(fd, I2C_SLAVE, address) == -1)
  {
    std::cerr << "Cannot set address for input module" << std::endl;
    return 0;
  }

  recvBufLen = ::read(fd, &recvBuf[0], quantity);
  if (recvBufLen == -1)
  {
    std::cerr << "Error reading from inputs." << std::endl;
    return 0;
  }
  readPos = &recvBuf[0];
  return recvBufLen;
}

int TwoWire::available(void) { return recvBufLen - (readPos - &recvBuf[0]); }

int TwoWire::read(void) { return *readPos++; }

TwoWire Wire = TwoWire();
