BIN_DIR = ./bin/
LIB_DIR = ./bin/lib/
OBJ_DIR = ./bin/obj/

CC = g++

DEBUG = -g
WARN = -Wall
FLAGS = $(WARN) -std=c++11 -I./ $(DEBUG)

CFLAGS = $(FLAGS) -c
LFLAGS = $(FLAGS)
MFLAGS = $(FLAGS) -fPIC -shared -o


OBJS = $(OBJ_DIR)Configurator.o $(OBJ_DIR)Thermostat.o $(OBJ_DIR)ThermostatComponent.o
MODS = ButtonSetPointController.so TestThermometer.so BangBangController.so TestThermalController.so SimpleLedDisplay.so
MODS += DS18B20Thermometer.so ControlOutputDisplay.so LcdDisplay.so
MODS += PowerSwitchTailController.so

Thermostat: $(OBJS)
	mkdir -p $(BIN_DIR)	
	$(CC) $(LFLAGS) $(OBJS) -o $(BIN_DIR)Thermostat -ldl -rdynamic

$(OBJ_DIR)Configurator.o: Configurator.cpp Configurator.h
	mkdir -p $(OBJ_DIR)	
	$(CC) $(CFLAGS) Configurator.cpp -o $(OBJ_DIR)Configurator.o

$(OBJ_DIR)Thermostat.o: Thermostat.cpp ThermostatComponent.h
	$(CC) $(CFLAGS) Thermostat.cpp -o $(OBJ_DIR)Thermostat.o

$(OBJ_DIR)ThermostatComponent.o: ThermostatComponent.h ThermostatComponent.cpp
	$(CC) $(CFLAGS) ThermostatComponent.cpp -o $(OBJ_DIR)ThermostatComponent.o

ButtonSetPointController.so: Interfaces/ISetPointController.h Modules/ButtonSetPointController.cpp
	mkdir -p $(LIB_DIR)	
	$(CC) $(MFLAGS) $(LIB_DIR)ButtonSetPointController.so Modules/ButtonSetPointController.cpp

BangBangController.so: Interfaces/ITemperatureControlAlgorithm.h Modules/BangBangController.cpp
	mkdir -p $(LIB_DIR)	
	$(CC) $(MFLAGS) $(LIB_DIR)BangBangController.so Modules/BangBangController.cpp

TestThermalController.so: Interfaces/IThermalController.h Modules/TestThermalController.cpp
	mkdir -p $(LIB_DIR)	
	$(CC) $(MFLAGS) $(LIB_DIR)TestThermalController.so Modules/TestThermalController.cpp

PowerSwitchTailController.so: Interfaces/IThermalController.h Modules/PowerSwitchTailController.cpp
	mkdir -p $(LIB_DIR)	
	$(CC) $(MFLAGS) $(LIB_DIR)PowerSwitchTailController.so Modules/PowerSwitchTailController.cpp

SimpleLedDisplay.so: Interfaces/IThermostatDisplay.h Modules/SimpleLedDisplay.cpp
	mkdir -p $(LIB_DIR)	
	$(CC) $(MFLAGS) $(LIB_DIR)SimpleLedDisplay.so Modules/SimpleLedDisplay.cpp $(OBJ_DIR)Configurator.o

LcdDisplay.so: Interfaces/IThermostatDisplay.h Modules/LcdDisplay.cpp
	mkdir -p $(LIB_DIR)	
	$(CC) $(MFLAGS) $(LIB_DIR)LcdDisplay.so Modules/LcdDisplay.cpp $(OBJ_DIR)Configurator.o -lboost_thread 

ControlOutputDisplay.so: Interfaces/IThermostatDisplay.h Modules/ControlOutputDisplay.cpp
	mkdir -p $(LIB_DIR)	
	$(CC) $(MFLAGS) $(LIB_DIR)ControlOutputDisplay.so Modules/ControlOutputDisplay.cpp

DS18B20Thermometer.so: Interfaces/IThermometer.h Modules/DS18B20Thermometer.cpp
	mkdir -p $(LIB_DIR)	
	$(CC) $(MFLAGS) $(LIB_DIR)DS18B20Thermometer.so Modules/DS18B20Thermometer.cpp -lboost_thread 

TestThermometer.so: Interfaces/IThermometer.h Modules/TestThermometer.cpp
	mkdir -p $(LIB_DIR)	
	$(CC) $(MFLAGS) $(LIB_DIR)TestThermometer.so Modules/TestThermometer.cpp


all: Thermostat $(OBJS) $(MODS)

clean:
	find -name "*~" -exec rm {} \;
	find -name "*.o" -exec rm {} \;
	find -name "*.so" -exec rm {} \;
	rm -rf ./bin


