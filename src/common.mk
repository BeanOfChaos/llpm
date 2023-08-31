COMMON_INCLUDED=yes

ROOT_DIR:=$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
CC=gcc
LD=ld
INCLUDE=$(ROOT_DIR)/../include
CFLAGS=-O2 -Wall -Wextra -Wfloat-equal -Wundef -Wshadow -Wpointer-arith -Wcast-align -Wstrict-prototypes -Wwrite-strings -Waggregate-return -Wcast-qual -Wswitch-default -Wswitch-enum -Wconversion -Wunreachable-code

BIN_DIR=$(ROOT_DIR)/../bin
LIB_DIR=$(ROOT_DIR)/../lib
BUILD_DIR=$(ROOT_DIR)/build

$(BUILD_DIR):
	mkdir $(BUILD_DIR)
$(BIN_DIR):
	mkdir $(BIN_DIR)
$(LIB_DIR):
	mkdir $(LIB_DIR)