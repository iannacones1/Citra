#include <iostream>
#include <fstream>

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
	  //	  std::cout << __FILE__ << "::" << __func__ << std::endl; 
	    write("/home/pi/.temp", "heat");

        }

        virtual void cool()
        {
	  //std::cout << __FILE__ << "::" << __func__ << std::endl; 
	    write("/home/pi/.temp", "cool");
        }

        virtual void stay()
        {
	  //std::cout << __FILE__ << "::" << __func__ << std::endl; 
	    write("/home/pi/.temp", "stay");
        }

    protected:
       void write(const std::string& inFileName, const std::string& inValue) const
       {
          std::ofstream aFileStream(inFileName.c_str());

    if (!aFileStream)
      {
	std::cout << " OPERATION FAILED: Unable to open file " << inFileName << std::endl;
	std::cout << " !!! MUST RUN AS ROOT to acess /sys/class/gpio/" << std::endl;
	return;
      }

    aFileStream << inValue;
    aFileStream.close();

  }

};

MODULE(Interfaces::IThermalController, TestThermalController);

} /* namespace thermostat */


