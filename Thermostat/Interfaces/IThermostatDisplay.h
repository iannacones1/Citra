#ifndef _I_THERMOSTAT_DISPLAY_H_
#define _I_THERMOSTAT_DISPLAY_H_

#include "ControlEnum.hpp"

namespace Citra { namespace Thermostat { namespace Interfaces {

class IThermostatDisplay
{
    public:
        IThermostatDisplay() {}
        virtual ~IThermostatDisplay() {}

        virtual void display(bool inOn, float inSetPoint, float inCurrentTemp, Control inControlAction) = 0;

};

} /* namespace Interfaces*/ } /* namespace Thermostat */ } /* namespace Citra */

#endif /* _I_THERMOSTAT_DISPLAY_H_ */
