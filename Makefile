BIN_DIR = ./bin/
LIB_DIR = ./bin/lib/
OBJ_DIR = ./bin/obj/

CC = g++

DEBUG = -g
WARN = -Wall -Wextra -Wpedantic
FLAGS = $(WARN) -std=c++14 -O3 -I./ $(DEBUG)

CFLAGS = $(FLAGS) -c
LFLAGS = $(FLAGS)
MFLAGS = $(FLAGS) -fPIC -shared -o

ALL =  

include Display/Makefile
include Language/Makefile
include Configurable/Makefile

include mlbClock/Makefile
include Thermostat/Makefile
include Http/Makefile

all: $(ALL)

clean:
	find -name "*~" -exec rm {} \;
	find -name "*.o" -exec rm {} \;
	find -name "*.so" -exec rm {} \;
	rm -rf ./bin


