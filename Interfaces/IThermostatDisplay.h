#ifndef _I_THERMOSTAT_DISPLAY_H_
#define _I_THERMOSTAT_DISPLAY_H_

#include "ControlEnum.hpp"
#include "Configurable.hpp"

namespace thermostat { namespace Interfaces {

class IThermostatDisplay
{
    public:
        IThermostatDisplay() {}
        virtual ~IThermostatDisplay() {}

        virtual void display(bool inOn, float inSetPoint, float inCurrentTemp, Control inControlAction) = 0;

};

} /* namespace Interfaces*/ } /* namespace thermostat */

#endif /* _I_THERMOSTAT_DISPLAY_H_ */
