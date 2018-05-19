#ifndef _I_THERMOMETER_H_
#define _I_THERMOMETER_H_

namespace Citra { namespace Thermostat { namespace Interfaces {

class IThermometer
{
    public:
        IThermometer() {}
        virtual ~IThermometer() {}

        virtual float currentTemperatureFahrenheit() = 0;

};

} /* namespace Interfaces*/ } /* namespace Thermostat */ } /* namespace Citra */

#endif /* _I_THERMOMETER_H_ */
