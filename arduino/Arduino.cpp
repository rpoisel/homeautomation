#include "Arduino.h"
#include <Poco/Timestamp.h>

#include <signal.h>
#include <time.h>

#include <atomic>
#include <cstdlib>

static void teardownWrapper(int sigNum);
static struct sigaction const* getTeardownAction(void);
static std::atomic_bool shutdownFlag(false);
static Poco::Timestamp startTime;

int main(void)
{
  sigaction(SIGINT, getTeardownAction(), nullptr);
  sigaction(SIGTERM, getTeardownAction(), nullptr);

  setup();
  while (!shutdownFlag)
  {
    loop();
  }
  teardown();

  return EXIT_SUCCESS;
}

static struct sigaction const* getTeardownAction(void)
{
  static struct sigaction const teardownAction = {
      teardownWrapper, // sa_handler
      0,               // sa_mask
      SA_RESTART,      // sa_flags
  };

  return &teardownAction;
}

static void teardownWrapper(int sigNum)
{
  (void)sigNum;
  shutdownFlag = true;
}

#pragma weak setup
void setup(void) {}

#pragma weak loop
void loop(void) {}

#pragma weak teardown
void teardown(void) {}

void delay(unsigned long ms)
{
  struct timespec const req = {
      .tv_sec = 0, .tv_nsec = (long)ms * 1000000 /* ms */
  };

  nanosleep(&req, 0);
}

unsigned long millis()
{
  Poco::Timestamp curTime;
  return (curTime - startTime) / 1000;
}

SerialClass Serial;