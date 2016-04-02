#ifndef _THERMOSTAT_COMPONENT_H_
#define _THERMOSTAT_COMPONENT_H_

#include <unistd.h>
#include <iostream>

#include "Interfaces/ISetPointController.h"
#include "Interfaces/IThermometer.h"
#include "Interfaces/ITemperatureControlAlgorithm.h"

namespace thermostat {

class ThermostatComponent
{
    public:
        ThermostatComponent(Interfaces::ISetPointController* inSetPointController,
	                    Interfaces::IThermometer* inThermometer,
                            Interfaces::ITemperatureControlAlgorithm* inControlAlgorithm);

        virtual ~ThermostatComponent();
        void run();
        void shutdown();

    protected:
        bool mShutdown;
        Interfaces::ISetPointController* mSetPointController;
        Interfaces::IThermometer* mThermometer;
        Interfaces::ITemperatureControlAlgorithm* mControlAlgorithm;
};

} /* namespace thermostat */

#endif /* _THERMOSTAT_COMPONENT_H_ */
