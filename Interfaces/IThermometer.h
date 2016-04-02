#ifndef _I_THERMOMETER_H_
#define _I_THERMOMETER_H_

namespace thermostat { namespace Interfaces {

class IThermometer
{
    public:
        IThermometer() {}
        virtual ~IThermometer() {}

        virtual float currentTemperatureFahrenheit() = 0;

};

} /* namespace Interfaces*/ } /* namespace thermostat */

#endif /* _I_THERMOMETER_H_ */
