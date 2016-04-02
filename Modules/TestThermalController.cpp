#include <iostream>

#include "../Interfaces/IThermalController.h"
#include "create_module_macro.h"

namespace thermostat {

class TestThermalController : public Interfaces::IThermalController
{
    public:
        TestThermalController() : Interfaces::IThermalController() { }
        virtual ~TestThermalController() { }

        virtual void heat()
        {
	    std::cout << __func__ << std::endl; 
        }

        virtual void cool()
        {
	    std::cout << __func__ << std::endl; 
        }
};

MODULE(Interfaces::IThermalController, TestThermalController);

} /* namespace thermostat */


