#ifndef _THERMOSTAT_COMPONENT_H_
#define _THERMOSTAT_COMPONENT_H_

#include <unistd.h>
#include <iostream>
#include <list>

#include "Interfaces/ISetPointController.h"
#include "Interfaces/IThermometer.h"
#include "Interfaces/ITemperatureControlAlgorithm.h"
#include "Interfaces/IThermalController.h"
#include "Interfaces/IThermostatDisplay.h"

#include "Module.hpp"

namespace thermostat {

class ThermostatComponent
{
    public:
        ThermostatComponent();
        virtual ~ThermostatComponent();
        void run();
        void shutdown();

    protected:
        CONFIGURABLE
	(
	    (std::string) SetPointController,
	    (std::string) Thermometer,
	    (std::string) ControlAlgorithm,
	    (std::string) ThermalController,
	    (std::list<std::string>) ThermostatDisplays
        )
	INITIALIZE(ThermostatComponent);

        bool mShutdown;
        Module<thermostat::Interfaces::ISetPointController> mSetPointController;
        Module<thermostat::Interfaces::IThermometer> mThermometer;
        Module<thermostat::Interfaces::ITemperatureControlAlgorithm> mControlAlgorithm;
        Module<thermostat::Interfaces::IThermalController> mThermalController;
	std::list<Module<thermostat::Interfaces::IThermostatDisplay> > mThermostatDisplayList;
};

} /* namespace thermostat */

#endif /* _THERMOSTAT_COMPONENT_H_ */
