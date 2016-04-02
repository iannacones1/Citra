#include "../Interfaces/ISetPointController.h"
#include "create_module_macro.h"

namespace thermostat {

class TestSetPointController : public Interfaces::ISetPointController
{
    public:
        TestSetPointController() : Interfaces::ISetPointController() { }
        virtual ~TestSetPointController() { }

        virtual bool isSetPointDefined() { return true; }
        virtual float currentSetPointFahrenheit() { return 150.0; }

};

MODULE(Interfaces::ISetPointController, TestSetPointController);

} /* namespace thermostat*/
