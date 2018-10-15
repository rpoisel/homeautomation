#include <linux/i2c-dev.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

#include <cstdint>
#include <cstdlib>
#include <iostream>

static char const* I2C_DEVICE_PATH = "/dev/i2c-1";
static uint8_t I2C_ADDR_OUT = 0x20;
static uint8_t I2C_ADDR_IN = 0x38;

int main(void)
{
  uint8_t states_inputs_curr, states_inputs_prev = 0xff, states_outputs = 0xff;
  int fd;
  ssize_t numBytes;
  struct timespec const req = {
    .tv_sec = 0,
    .tv_nsec = 50000000LL /* ms */
  };

  fd = open(I2C_DEVICE_PATH, O_RDWR);
  if (fd == -1)
  {
    std::cerr << "Failed to open I2C bus." << std::endl;
    return EXIT_FAILURE;
  }

  for(;;)
  {
    if (ioctl(fd, I2C_SLAVE, I2C_ADDR_IN) == -1)
    {
      std::cerr << "Cannot set address for input module" << std::endl;
      return EXIT_FAILURE;
    }

    numBytes = read(fd, &states_inputs_curr, 1);
    if (numBytes == -1)
    {
      std::cerr << "Error reading from inputs." << std::endl;
    }

    states_outputs ^= ((~states_inputs_prev) & states_inputs_curr);

    if (ioctl(fd, I2C_SLAVE, I2C_ADDR_OUT) == -1)
    {
      std::cerr << "Cannot set address for output module" << std::endl;
      return EXIT_FAILURE;
    }

    numBytes = write(fd, &states_outputs, 1);
    if (numBytes == -1)
    {
      std::cerr << "Error writing inputs." << std::endl;
    }

    nanosleep(&req, 0);
    states_inputs_prev = states_inputs_curr;
  }

  close(fd);

  return EXIT_SUCCESS;
}
