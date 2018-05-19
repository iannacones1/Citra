CONFIGURABLE_OBJS = $(OBJ_DIR)IConfigurator.o $(OBJ_DIR)CommandLineConfigurator.o $(OBJ_DIR)FileConfigurator.o

$(OBJ_DIR)IConfigurator.o: Configurable/IConfigurator.cpp Configurable/IConfigurator.h
	mkdir -p $(OBJ_DIR)	
	$(CC) $(CFLAGS) Configurable/IConfigurator.cpp -o $(OBJ_DIR)IConfigurator.o

$(OBJ_DIR)CommandLineConfigurator.o: Configurable/Configurators/CommandLineConfigurator.cpp Configurable/Configurators/CommandLineConfigurator.h
	mkdir -p $(OBJ_DIR)	
	$(CC) $(CFLAGS) Configurable/Configurators/CommandLineConfigurator.cpp -o $(OBJ_DIR)CommandLineConfigurator.o

$(OBJ_DIR)FileConfigurator.o: Configurable/Configurators/FileConfigurator.cpp Configurable/Configurators/FileConfigurator.h
	mkdir -p $(OBJ_DIR)	
	$(CC) $(CFLAGS) Configurable/Configurators/FileConfigurator.cpp -o $(OBJ_DIR)FileConfigurator.o

ALL += $(CONFIGURABLE_OBJS)
