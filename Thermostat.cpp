#include <iostream>
#include <csignal>
#include <list>

#include "ThermostatComponent.h"

#include "Module.hpp"
#include "Interfaces/ISetPointController.h"
#include "Interfaces/IThermometer.h"
#include "Interfaces/ITemperatureControlAlgorithm.h"
#include "Interfaces/IThermalController.h"
#include "Interfaces/IThermostatDisplay.h"

#include "Configurator.h"

static thermostat::ThermostatComponent* aThermostatPtr;

void signalHandler(int inSigNum)
{
    if (aThermostatPtr) { aThermostatPtr->shutdown(); }
}

int main(int argc, char* argv[])
{
    signal(SIGINT, signalHandler);

    std::cout << "Running " << argv[0] << std::endl;

    {
        thermostat::Configurator::Instance()->addFileData("../config/ThermostatComponentConfig.txt");

        thermostat::ThermostatComponent aThermostat;

        aThermostatPtr = &aThermostat;

        aThermostat.run();
    }

    std::cout << "(DONE)" << std::endl;

    return 0;
}
