#include "../Interfaces/IThermometer.h"
#include "create_module_macro.h"

namespace thermostat {

class TestThermometer : public Interfaces::IThermometer
{
    public:
        TestThermometer() : Interfaces::IThermometer() { }
        virtual ~TestThermometer() { }

        virtual float currentTemperatureFahrenheit() { return 130.0; }
};

MODULE(Interfaces::IThermometer, TestThermometer);

} /* namespace thermostat*/
