#!/bin/sh

cp $1 ../libmaple/main.cpp
cd ../libmaple
make clean;make;make install
