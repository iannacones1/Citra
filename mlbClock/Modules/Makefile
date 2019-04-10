CAIRO_INCLUDE := -I/usr/include/cairo/ -I/usr/include/cairomm-1.0/

$(LIB_DIR)CairoMlbImageBuilder.so: mlbClock/Modules/CairoMlbImageBuilder.cpp
	mkdir -p $(LIB_DIR)
	$(CC) $(CAIRO_INCLUDE) $(MFLAGS) $(LIB_DIR)CairoMlbImageBuilder.so mlbClock/Modules/CairoMlbImageBuilder.cpp -lcairo

$(LIB_DIR)QtMlbImageBuilder.so: mlbClock/Modules/QtMlbImageBuilder.cpp
	mkdir -p $(LIB_DIR)
	$(CC) $(QT_INCLUDE) $(MFLAGS) $(LIB_DIR)QtMlbImageBuilder.so mlbClock/Modules/QtMlbImageBuilder.cpp -lQtGui -lQtCore -lpthread

$(LIB_DIR)XmlDataGrabber.so: mlbClock/Modules/XmlDataGrabber.cpp $(OBJ_DIR)httpClient.o
	mkdir -p $(LIB_DIR)
	$(CC) $(MFLAGS) $(LIB_DIR)XmlDataGrabber.so mlbClock/Modules/XmlDataGrabber.cpp $(OBJ_DIR)httpClient.o -lboost_date_time -lboost_system

$(LIB_DIR)JsonDataGrabber.so: mlbClock/Modules/JsonDataGrabber.cpp
	mkdir -p $(LIB_DIR)
	$(CC) $(MFLAGS) $(LIB_DIR)JsonDataGrabber.so mlbClock/Modules/JsonDataGrabber.cpp

# If cairo include dir is missing then don't add target to MLB_CLOCK_MODS
ifeq ($(shell [ -d /usr/include/cairo/ ] && echo "FOUND"),FOUND)
	MLB_CLOCK_MODS += $(LIB_DIR)CairoMlbImageBuilder.so
else
    $(info ommiting CairoMlbImageBuilder from MLB_CLOCK_MODS)
endif

# If qt4 include dir is missing then don't add target to MLB_CLOCK_MODS
qt_dir = $(shell [ -d /usr/include/qt4/ ] && echo "FOUND")
ifeq ($(qt_dir),FOUND)
	MLB_CLOCK_MODS += $(LIB_DIR)QtMlbImageBuilder.so
else
    $(info ommiting QtMlbImageBuilder from MLB_CLOCK_MODS)
endif

MLB_CLOCK_MODS += $(LIB_DIR)XmlDataGrabber.so
MLB_CLOCK_MODS += $(LIB_DIR)JsonDataGrabber.so

ALL += $(MLB_CLOCK_MODS)