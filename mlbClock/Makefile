MLB_CLOCK_OBJS := $(OBJ_DIR)mlbClock.o $(OBJ_DIR)mlbClockComponent.o

QT_INCLUDE := -I/usr/include/qt4/

mlbClock: $(MLB_CLOCK_OBJS) $(EPD_OBJS) 
	mkdir -p $(BIN_DIR)	
	$(CC) $(LFLAGS) $(QT_INCLUDE) $(EPD_OBJS) $(MLB_CLOCK_OBJS) -o $(BIN_DIR)mlbClock -ldl -rdynamic -ljsoncpp -lQtGui -lQtCore $(EPD_LINK)

$(OBJ_DIR)mlbClock.o: mlbClock/mlbClock.cpp mlbClock/mlbClockComponent.h
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(QT_INCLUDE) mlbClock/mlbClock.cpp -o $(OBJ_DIR)mlbClock.o

$(OBJ_DIR)mlbClockComponent.o: mlbClock/mlbClockComponent.h mlbClock/mlbClockComponent.cpp
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(QT_INCLUDE) mlbClock/mlbClockComponent.cpp -o $(OBJ_DIR)mlbClockComponent.o
	
ALL += mlbClock $(MLB_CLOCK_OBJS)
