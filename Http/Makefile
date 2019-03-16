
httpExample: $(OBJ_DIR)httpExample.o $(OBJ_DIR)httpClient.o
	mkdir -p $(BIN_DIR)	
	$(CC) $(FLAGS) -o $(BIN_DIR)httpExample $(OBJ_DIR)httpExample.o $(OBJ_DIR)httpClient.o -lboost_system -lpthread

$(OBJ_DIR)httpExample.o: Http/httpExample.cpp
	mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) -c Http/httpExample.cpp -o $(OBJ_DIR)httpExample.o

$(OBJ_DIR)httpClient.o: Http/httpClient.cpp
	mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) -c Http/httpClient.cpp -o $(OBJ_DIR)httpClient.o
	
