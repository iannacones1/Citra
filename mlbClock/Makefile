CLOCK_MODS_DIR := mlbClock/Modules/
MLB_CLOCK_OBJS := $(OBJ_DIR)mlbClock.o $(OBJ_DIR)mlbClockComponent.o
DEV_CLOCK_OBJS := $(OBJ_DIR)devMlbClock.o 
MLB_CLOCK_MODS := $(patsubst %.cpp, %.so, $(wildcard $(CLOCK_MODS_DIR)*.cpp))

QT_INCLUDE := -I/usr/include/qt4/
CAIRO_INCLUDE := -I/usr/include/cairo/ -I/usr/include/cairomm-1.0/

mlbClock: $(CONFIGURABLE_OBJS) $(MLB_CLOCK_OBJS) $(MLB_CLOCK_MODS)
	mkdir -p $(BIN_DIR)	
	$(CC) $(LFLAGS) $(CONFIGURABLE_OBJS) $(MLB_CLOCK_OBJS) -o $(BIN_DIR)mlbClock -ldl -rdynamic

$(OBJ_DIR)mlbClock.o: mlbClock/mlbClock.cpp mlbClock/mlbClockComponent.h
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) mlbClock/mlbClock.cpp -o $(OBJ_DIR)mlbClock.o

$(OBJ_DIR)mlbClockComponent.o: mlbClock/mlbClockComponent.h mlbClock/mlbClockComponent.cpp
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) mlbClock/mlbClockComponent.cpp -o $(OBJ_DIR)mlbClockComponent.o

devMlbClock: $(DEV_CLOCK_OBJS)
	mkdir -p $(BIN_DIR)	
	$(CC) $(LFLAGS) $(QT_INCLUDE) $(DEV_CLOCK_OBJS) -o $(BIN_DIR)devMlbClock -ldl -rdynamic -lQtGui -lQtCore

$(OBJ_DIR)devMlbClock.o: mlbClock/devMlbClock.cpp
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(QT_INCLUDE) mlbClock/devMlbClock.cpp -o $(OBJ_DIR)devMlbClock.o

$(CLOCK_MODS_DIR)%.so: $(CLOCK_MODS_DIR)%.cpp
	mkdir -p $(LIB_DIR)
	$(CC) $(QT_INCLUDE) $(CAIRO_INCLUDE) $(MFLAGS) $(LIB_DIR)$(notdir $@) $< -lboost_date_time -lQtGui -lQtCore -lcairo
	
ALL += mlbClock $(MLB_CLOCK_OBJS) $(MLB_CLOCK_MODS) devMlbClock $(DEV_CLOCK_OBJS)
