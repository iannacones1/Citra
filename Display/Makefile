EPD_OBJS := $(OBJ_DIR)EinkDisplay.o
EPD_LINK := -lbcm2835

$(OBJ_DIR)EinkDisplay.o: Display/EinkDisplay.cpp Display/EinkDisplay.h Display/ImageBuffer.hpp
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) Display/EinkDisplay.cpp -o $(OBJ_DIR)EinkDisplay.o $(EPD_LINK)

ALL += $(EPD_OBJS)