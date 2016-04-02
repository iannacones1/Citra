#include "../Interfaces/ITemperatureControlAlgorithm.h"
#include "create_module_macro.h"

namespace thermostat {

class BangBangController : public Interfaces::ITemperatureControlAlgorithm
{
    public:
        BangBangController() : Interfaces::ITemperatureControlAlgorithm() { }
        virtual ~BangBangController() { }

        virtual Interfaces::Control controlTemperatureFahrenheit(float inSetpointFahrenheit, float inTemperature)
        {
            if (inSetpointFahrenheit > inTemperature) { return Interfaces::HEAT; }
	    if (inSetpointFahrenheit < inTemperature) { return Interfaces::COOL; }
	    return Interfaces::STAY;
        }
};

MODULE(Interfaces::ITemperatureControlAlgorithm, BangBangController);

} /* namespace thermostat */
