#ifndef _I_TEMPERATURE_CONTROL_ALGORITHM_H_
#define _I_TEMPERATURE_CONTROL_ALGORITHM_H_

#include "ControlEnum.hpp"

namespace thermostat { namespace Interfaces {

class ITemperatureControlAlgorithm
{
    public:
        ITemperatureControlAlgorithm() {}
        virtual ~ITemperatureControlAlgorithm() {}

        virtual Control controlTemperatureFahrenheit(float inSetpointFahrenheit, float inTemperature) = 0;
};

} /* namespace Interfaces*/ } /* namespace thermostat */

#endif /* _I_TEMPERATURE_CONTROL_ALGORITHM_H_ */
