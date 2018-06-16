#include <iostream>
#include <csignal>

#include <Thermostat/ThermostatComponent.h>

#include <Configurable/Configurators/FileConfigurator.h>
#include <Configurable/Configurators/CommandLineConfigurator.h>

static Citra::Thermostat::ThermostatComponent* aThermostatPtr;

void signalHandler(int /* inSigNum */)
{
    if (aThermostatPtr) { aThermostatPtr->shutdown(); }
}

int main(int argc, char* argv[])
{
    signal(SIGINT, signalHandler);

    std::cout << "Running " << argv[0] << std::endl;

    {
        Citra::Configurable::FileConfigurator aConfigurator(argc, argv, "../Thermostat/configs/TestThermostatComponentConfig.txt");
//        Citra::Configurable::FileConfigurator bConfigurator(argc, argv, "../Thermostat/configs/ThermostatComponentConfig.txt");
//    	  Citra::Configurable::CommandLineConfigurator cConfigurator(argc, argv);

        Citra::Thermostat::ThermostatComponent aThermostat;

        if (Citra::Configurable::IConfigurator::help())
        {
            std::cout << "(HELP DONE)" << std::endl;
            return 0;
        }

        aThermostatPtr = &aThermostat;

        aThermostat.run();
    }

    std::cout << "(DONE)" << std::endl;

    return 0;
}
