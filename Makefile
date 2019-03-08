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

httpClient: $(OBJ_DIR)httpClient.o
	$(CC) $(FLAGS) $(OBJ_DIR)httpClient.o -o $(BIN_DIR)httpClient

$(OBJ_DIR)httpClient.o: http_client_sync.cpp
	$(CC) $(FLAGS) http_client_sync.cpp -o $(OBJ_DIR)httpClient.o

all: $(ALL)

clean:
	find -name "*~" -exec rm {} \;
	find -name "*.o" -exec rm {} \;
	find -name "*.so" -exec rm {} \;
	rm -rf ./bin


