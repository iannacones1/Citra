#include <iostream>
#include <fstream>

#include <Thermostat/Interfaces/IThermalController.h>
#include <Module/create_module_macro.h>

namespace Citra { namespace Thermostat {

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
	            std::cerr << " OPERATION FAILED: Unable to open file " << inFileName << std::endl;
	            return;
            }

            aFileStream << inValue;
            aFileStream.close();
        }
};

MODULE(Interfaces::IThermalController, TestThermalController)

} /* namespace Thermostat*/ } /* namespace Citra */
