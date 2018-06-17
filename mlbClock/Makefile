CLOCK_MODS_DIR := mlbClock/Modules/
MLB_CLOCK_OBJS := $(OBJ_DIR)mlbClock.o $(OBJ_DIR)mlbClockComponent.o
MLB_CLOCK_MODS := $(patsubst %.cpp, %.so, $(wildcard $(CLOCK_MODS_DIR)*.cpp))

QT_INCLUDE := -I/usr/include/qt4/

mlbClock: $(CONFIGURABLE_OBJS) $(MLB_CLOCK_OBJS)
	mkdir -p $(BIN_DIR)	
	$(CC) $(LFLAGS) $(QT_INCLUDE) $(CONFIGURABLE_OBJS) $(MLB_CLOCK_OBJS) -o $(BIN_DIR)mlbClock -ldl -rdynamic -lQtGui -lQtCore

$(OBJ_DIR)mlbClock.o: mlbClock/mlbClock.cpp mlbClock/mlbClockComponent.h
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(QT_INCLUDE) mlbClock/mlbClock.cpp -o $(OBJ_DIR)mlbClock.o

$(OBJ_DIR)mlbClockComponent.o: mlbClock/mlbClockComponent.h mlbClock/mlbClockComponent.cpp
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(QT_INCLUDE) mlbClock/mlbClockComponent.cpp -o $(OBJ_DIR)mlbClockComponent.o

$(CLOCK_MODS_DIR)%.so: $(CLOCK_MODS_DIR)%.cpp
	mkdir -p $(LIB_DIR)
	$(CC) $(MFLAGS) $(LIB_DIR)$(notdir $@) $<
	
ALL += mlbClock $(MLB_CLOCK_OBJS) $(MLB_CLOCK_MODS)
