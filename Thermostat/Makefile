THER_MOD_DIR    := Thermostat/Modules/
THERMOSTAT_OBJS := $(OBJ_DIR)Thermostat.o $(OBJ_DIR)ThermostatComponent.o
THERMOSTAT_MODS := $(patsubst %.cpp, %.so, $(wildcard $(THER_MOD_DIR)*.cpp))

Thermostat: $(CONFIGURABLE_OBJS) $(THERMOSTAT_OBJS)
	mkdir -p $(BIN_DIR)	
	$(CC) $(LFLAGS) $(CONFIGURABLE_OBJS) $(THERMOSTAT_OBJS) -o $(BIN_DIR)Thermostat -ldl -rdynamic

$(OBJ_DIR)Thermostat.o: Thermostat/Thermostat.cpp Thermostat/ThermostatComponent.h
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) Thermostat/Thermostat.cpp -o $(OBJ_DIR)Thermostat.o

$(OBJ_DIR)ThermostatComponent.o: Thermostat/ThermostatComponent.h Thermostat/ThermostatComponent.cpp
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) Thermostat/ThermostatComponent.cpp -o $(OBJ_DIR)ThermostatComponent.o

$(THER_MOD_DIR)%.so: $(THER_MOD_DIR)%.cpp
	mkdir -p $(LIB_DIR)
	$(CC) $(MFLAGS) $(LIB_DIR)$(notdir $@) $< -lboost_thread

ALL += Thermostat $(THERMOSTAT_OBJS) $(THERMOSTAT_MODS)
