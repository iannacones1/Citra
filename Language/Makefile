LoopLockListTest: $(OBJ_DIR)LoopLockListTest.o
	mkdir -p $(BIN_DIR)	
	$(CC) $(LFLAGS) $(OBJ_DIR)LoopLockListTest.o -o $(BIN_DIR)LoopLockListTest -ldl -lboost_thread -lboost_system -rdynamic

$(OBJ_DIR)LoopLockListTest.o: LoopLockListTest.cpp
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) LoopLockListTest.cpp -o $(OBJ_DIR)LoopLockListTest.o

ALL += LoopLockListTest $(OBJ_DIR)LoopLockListTest.o 