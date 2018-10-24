set(RASPBERRY_DIR_BASE /usr/local/toolchains/armv6-logicals-linux-gnueabihf)
set(RASPBERRY_DIR_COMPILER ${RASPBERRY_DIR_BASE}/bin)

set(CMAKE_C_COMPILER ${RASPBERRY_DIR_COMPILER}/armv6-logicals-linux-gnueabihf-gcc)
set(CMAKE_CXX_COMPILER ${RASPBERRY_DIR_COMPILER}/armv6-logicals-linux-gnueabihf-g++)
