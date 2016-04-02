OBJS = Thermostat.o ThermostatComponent.o
MODS = TestSetPointController.so TestThermometer.so BangBangController.so TestThermalController.so

CC=$(HOME)/x-tools/arm-rpi-linux-gnueabi/bin/arm-rpi-linux-gnueabi-g++
DEBUG = -g
CFLAGS = -Wall -std=c++11 -c $(DEBUG)

LFLAGS = -Wall $(DEBUG)
MFLAGS = -shared -o

Thermostat: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o Thermostat -ldl

Thermostat.o: Thermostat.cpp ThermostatComponent.h
	$(CC) $(CFLAGS) Thermostat.cpp

ThermostatComponent.o: ThermostatComponent.h ThermostatComponent.cpp
	$(CC) $(CFLAGS) ThermostatComponent.cpp

TestSetPointController.so: Interfaces/ISetPointController.h Modules/TestSetPointController.cpp
	$(CC) $(MFLAGS) TestSetPointController.so Modules/TestSetPointController.cpp

TestThermometer.so: Interfaces/IThermometer.h Modules/TestThermometer.cpp
	$(CC) $(MFLAGS) TestThermometer.so Modules/TestThermometer.cpp

BangBangController.so: Interfaces/ITemperatureControlAlgorithm.h Modules/BangBangController.cpp
	$(CC) $(MFLAGS) BangBangController.so Modules/BangBangController.cpp

TestThermalController.so: Interfaces/IThermalController.h Modules/TestThermalController.cpp
	$(CC) $(MFLAGS) TestThermalController.so Modules/TestThermalController.cpp

all: Thermostat $(MODS)

clean:
	rm *.so *.o *~ Thermostat


