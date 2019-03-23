#include <iostream>

#include <mlbClock/mlbClockComponent.h>

#include <Configurable/Configurators/FileConfigurator.h>
#include <Configurable/Configurators/CommandLineConfigurator.h>

int main(int argc, char* argv[])
{
    std::cout << "Running " << argv[0] << std::endl;

    Citra::Configurable::CommandLineConfigurator aConfigurator(argc, argv);

    Citra::mlbClock::mlbClockComponent aComponent;

    if (Citra::Configurable::IConfigurator::help())
    {
        std::cout << "(HELP DONE)" << std::endl;
        return 0;
    }

    aComponent.update();

    std::cout << "(DONE)" << std::endl;
    return 0;
}
