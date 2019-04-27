MLB_CLOCK_OBJS := $(OBJ_DIR)mlbClock.o $(OBJ_DIR)mlbClockComponent.o
MLB_CLOCK_MODS :=

QT_INCLUDE := -I/usr/include/qt4/

include mlbClock/Modules/Makefile

mlbClock: $(CONFIGURABLE_OBJS) $(MLB_CLOCK_OBJS)
	mkdir -p $(BIN_DIR)
	$(CC) $(LFLAGS) $(CONFIGURABLE_OBJS) $(MLB_CLOCK_OBJS) -o $(BIN_DIR)mlbClock -ldl -rdynamic

mlbClock: | $(MLB_CLOCK_MODS) devMlbClock

$(OBJ_DIR)mlbClock.o: mlbClock/mlbClock.cpp
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) mlbClock/mlbClock.cpp -o $(OBJ_DIR)mlbClock.o

$(OBJ_DIR)mlbClockComponent.o: mlbClock/mlbClockComponent.cpp
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) mlbClock/mlbClockComponent.cpp -o $(OBJ_DIR)mlbClockComponent.o

devMlbClock: mlbClock/devMlbClock
	mkdir -p $(BIN_DIR)
	cp mlbClock/devMlbClock $(BIN_DIR)devMlbClock
	chmod 755 $(BIN_DIR)devMlbClock

ALL += mlbClock $(MLB_CLOCK_OBJS) devMlbClock
