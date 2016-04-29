#include <iostream>
#include <fstream>

#include "Interfaces/IThermalController.h"
#include "create_module_macro.h"

namespace thermostat {

class TestThermalController : public Interfaces::IThermalController
{
    public:
        TestThermalController() : Interfaces::IThermalController() { }
        virtual ~TestThermalController() { }

        virtual void heat() { write("/home/pi/.temp", "heat"); }
        virtual void cool() { write("/home/pi/.temp", "cool"); }
        virtual void stay() { write("/home/pi/.temp", "stay"); }

    protected:
        void write(const std::string& inFileName, const std::string& inValue) const
        {
            std::ofstream aFileStream(inFileName.c_str());

            if (!aFileStream)
            {
	        std::cout << " OPERATION FAILED: Unable to open file " << inFileName << std::endl;
	        return;
            }

            aFileStream << inValue;
            aFileStream.close();
        }
};

MODULE(Interfaces::IThermalController, TestThermalController);

} /* namespace thermostat */


