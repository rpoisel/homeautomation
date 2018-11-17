#!/bin/bash

SRC_DIR=~/git/homeautomation
BLD_DIR=/tmp/build.homeautomation.linux-arm11

(
	rm -rf ${BLD_DIR} &&
	mkdir ${BLD_DIR} &&
	cd ${BLD_DIR} &&
	conan install ${SRC_DIR} -pr=raspberry-gcc-8 &&
	#conan install ${SRC_DIR} -pr=raspberry-gcc-8 --build paho-c --build zlib --build OpenSSL --build paho-cpp --build Poco &&
	cmake -GNinja \
		-DCMAKE_BUILD_TYPE=Debug \
		-DCMAKE_TOOLCHAIN_FILE=${SRC_DIR}/build-scripts/cmake/toolchain/toolchain.linux-arm11.cmake \
		-DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
		${SRC_DIR} &&
	ninja -v docker
)
