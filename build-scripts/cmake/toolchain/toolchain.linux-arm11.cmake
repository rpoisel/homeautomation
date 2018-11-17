set(RASPBERRY_DIR_BASE /usr/local/toolchains/armv7-rpi2-linux-gnueabihf)
set(RASPBERRY_DIR_COMPILER ${RASPBERRY_DIR_BASE}/bin)

set(CMAKE_C_COMPILER ${RASPBERRY_DIR_COMPILER}/armv7-rpi2-linux-gnueabihf-gcc)
set(CMAKE_CXX_COMPILER ${RASPBERRY_DIR_COMPILER}/armv7-rpi2-linux-gnueabihf-g++)
