#include <iostream>
#include <csignal>

#include <QtGui/QtGui>

#include <mlbClock/mlbClockComponent.h>

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
    	Citra::mlbClock::mlbClockComponent aComponent;

        aMlbClockPtr = &aComponent;

        aComponent.run();
    }

    std::cout << "(DONE)" << std::endl;
    return 0;
}
