#include "Interfaces/IThermometer.h"
#include "create_module_macro.h"

#include <iostream>
#include <fstream>
#include <queue>

namespace thermostat {

class TestThermometer : public Interfaces::IThermometer
{
    public:
  TestThermometer() : Interfaces::IThermometer(), mTestTemp(145.0), heater(0), cooler(0) { }
        virtual ~TestThermometer() { }

        virtual float currentTemperatureFahrenheit()
        { 
            std::string txt;
	    std::ifstream file("/home/pi/.temp");
    
	    if (file.is_open())
            {
	      while (file.good()) { getline(file, txt); }
	      file.close();
              mQ.push(txt);
	    }
	  
	    if (mQ.size() /* >= 5 */)
	    {
                txt = mQ.front();
                mQ.pop();
            
                if (txt == "heat")
                { 
  		    cooler = 0;
  		    heater = 0.1;
                    mTestTemp += heater;
                }
		else if (txt == "cool")
                { 
		    heater = 0;
                    cooler = 0.1;
                    mTestTemp -= cooler;
                }
		else
		{
		  heater = 0;
		  cooler = 0;
		}
	    }

	    return mTestTemp;
        }

        float mTestTemp;
  float heater;
  float cooler;
        std::queue<std::string> mQ;

};

MODULE(Interfaces::IThermometer, TestThermometer);

} /* namespace thermostat*/
