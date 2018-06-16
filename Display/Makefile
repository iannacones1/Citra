DISP_MOD_DIR := Display/Modules/
DISPLAY_OBJS := $(OBJ_DIR)EinkDisplay.o
DISPLAY_MODS := $(patsubst %.cpp, %.so, $(wildcard $(DISP_MOD_DIR)*.cpp))
DISPLAY_LINK := -lbcm2835

$(OBJ_DIR)EinkDisplay.o: Display/EinkDisplay.cpp Display/EinkDisplay.h Display/ImageBuffer.hpp
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) Display/EinkDisplay.cpp -o $(OBJ_DIR)EinkDisplay.o $(DISPLAY_LINK)

$(DISP_MOD_DIR)%.so: $(DISP_MOD_DIR)%.cpp $(DISPLAY_OBJS)
	mkdir -p $(LIB_DIR)
	$(CC) $(MFLAGS) $(LIB_DIR)$(notdir $@) $< $(DISPLAY_OBJS) $(DISPLAY_LINK)
	
ALL += $(DISPLAY_OBJS) $(DISPLAY_MODS)
