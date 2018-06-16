#include <iostream>
#include <csignal>

#include <QtGui/QtGui>

#include <mlbClock/mlbClockComponent.h>

#include <Configurable/Configurators/FileConfigurator.h>
#include <Configurable/Configurators/CommandLineConfigurator.h>

static Citra::mlbClock::mlbClockComponent* aMlbClockPtr;

void signalHandler(int /* inSigNum */)
{
    if (aMlbClockPtr) { aMlbClockPtr->shutdown(); }
}

int main(int argc, char* argv[])
{
	signal(SIGINT, signalHandler);

    QApplication app(argc, argv);

    std::cout << "Running " << argv[0] << std::endl;

    {
      Citra::Configurable::FileConfigurator aConfigurator(argc, argv, "../mlbClock/configs/mlbClockComponentConfig.txt");

    	Citra::mlbClock::mlbClockComponent aComponent;

    	if (Citra::Configurable::IConfigurator::help())
    	{
    	    std::cout << "(HELP DONE)" << std::endl;
    	    return 0;
    	}

        aMlbClockPtr = &aComponent;

        aComponent.run();
    }

    std::cout << "(DONE)" << std::endl;
    return 0;
}
