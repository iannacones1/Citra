#include <iostream>
#include <csignal>

#include "ThermostatComponent.h"

#include "Module.hpp"
#include "Interfaces/ISetPointController.h"
#include "Interfaces/IThermometer.h"
#include "Interfaces/ITemperatureControlAlgorithm.h"
#include "Interfaces/IThermalController.h"
#include "Interfaces/IThermostatDisplay.h"


static thermostat::ThermostatComponent* aThermostatPtr;

void signalHandler(int inSigNum)
{
    std::cout << __func__  << "(" << inSigNum << ")" << std::endl;

    if (aThermostatPtr) { aThermostatPtr->shutdown(); }
}

int main(int argc, char* argv[])
{
    signal(SIGINT, signalHandler);

    std::cout << "Running " << argv[0] << std::endl;

    {
        Module<thermostat::Interfaces::ISetPointController> aSetPoint("./TestSetPointController.so");
        Module<thermostat::Interfaces::IThermometer> aThermometer("./TestThermometer.so");
        Module<thermostat::Interfaces::ITemperatureControlAlgorithm> aAlgorithm("./BangBangController.so");
        Module<thermostat::Interfaces::IThermalController> aController("./TestThermalController.so");
        Module<thermostat::Interfaces::IThermostatDisplay> aDisplay("./SimpleLedDisplay.so");

        thermostat::ThermostatComponent aThermostat(aSetPoint.get(),
                                                    aThermometer.get(),
                                                    aAlgorithm.get(),
                                                    aController.get(),
                                                    aDisplay.get());
        aThermostatPtr = &aThermostat;

        aThermostat.run();
    }

    std::cout << "(DONE)" << std::endl;

    return 0;
}
