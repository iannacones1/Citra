#ifndef _THERMOSTAT_COMPONENT_H_
#define _THERMOSTAT_COMPONENT_H_

#include <unistd.h>
#include <iostream>
#include <list>

#include <Module/Module.hpp>
#include <Configurable/Configurable.hpp>

#include "Interfaces/ISetPointController.h"
#include "Interfaces/IThermometer.h"
#include "Interfaces/ITemperatureControlAlgorithm.h"
#include "Interfaces/IThermalController.h"
#include "Interfaces/IThermostatDisplay.h"


namespace Citra { namespace Thermostat {

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

	    INITIALIZE(ThermostatComponent)

        bool mShutdown;
        Module<Interfaces::ISetPointController> mSetPointController;
        Module<Interfaces::IThermometer> mThermometer;
        Module<Interfaces::ITemperatureControlAlgorithm> mControlAlgorithm;
        Module<Interfaces::IThermalController> mThermalController;
	    std::list<Module<Interfaces::IThermostatDisplay> > mThermostatDisplayList;
};

} /* namespace Thermostat */ } /* namespace Citra */

#endif /* _THERMOSTAT_COMPONENT_H_ */
