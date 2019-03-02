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
	
EinkSet: $(OBJ_DIR)EinkSet.o  $(DISPLAY_OBJS)
	mkdir -p $(BIN_DIR)	
	$(CC) $(LFLAGS)  $(DISPLAY_OBJS) $(OBJ_DIR)EinkSet.o -o $(BIN_DIR)EinkSet $(DISPLAY_LINK)

$(OBJ_DIR)EinkSet.o: Display/EinkSet.cpp
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) Display/EinkSet.cpp -o $(OBJ_DIR)EinkSet.o
	
ALL += $(DISPLAY_OBJS) $(DISPLAY_MODS) $(OBJ_DIR)EinkSet.o EinkSet