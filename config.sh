#!/bin/sh

# Location of toolchain in the Ubuntu VM PDA1 /opt/ti-processor-sdk-linux-rt-am57xx-evm-05.02.00.10/linux-devkit/sysroots/x86_64-arago-linux/usr/bin
# Though it is ti processor toolchain, it should be a general cross compiler for other ARM Linux systems

 ./configure CC=arm-linux-gnueabihf-gcc CXX=arm-linux-gnueabihf-g++ AR=arm-linux-gnueabihf-ar LD=arm-linux-gnueabihf-ld RANLIB=arm-linux-gnueabihf-ranlib --host=arm-linux-gnueabihf --target=arm -prefix=/home/sagar/otis/python3_install --without-sqlite3 --without-pdo-sqlite --without-pear --enable-simplexml --disable-mbregex --enable-sockets --enable-fpm --disable-opcache --enable-libxml --without-zlib --with-libxml-dir=/home/sagar/otis/libxml/_install/ --build=x86_64-linux-gnu  --disable-all --disable-ipv6 ac_cv_have_long_long_format=yes ac_cv_file__dev_ptmx=no ac_cv_file__dev_ptc=no

