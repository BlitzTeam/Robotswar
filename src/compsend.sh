#!/bin/sh

cp $1 ../libmaple/main.cpp

cd ../libmaple
cat Makefile | sed '/USER_MODULES:=$(shell find .*/d' > /tmp/tm1
cat /tmp/tm1 | sed '/TARGET_FLAGS += -I..\/src\/libraries/d' > /tmp/tm
cat /tmp/tm | sed -e 's/\(# Try "make help" first.*\)/USER_MODULES:=$\(shell find ..\/src\/libraries\/ -name "*.mk" -exec dirname {} \\; | uniq\)\nLIBRARIES_PATH+=..\/src\/libraries\n\1/' > /tmp/tm1
cat /tmp/tm1 | sed -e 's/\(GLOBAL_CFLAGS   := .*\)/TARGET_FLAGS += -I..\/src\/libraries\n\1/' > Makefile


make clean;make;make install;
