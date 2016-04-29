#ifndef _GPIN_HPP_
#define _GPIN_HPP_

#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

#include "GPIO.hpp"

namespace thermostat {

// http://hertaville.com/introduction-to-accessing-the-raspberry-pis-gpio-in-c.html
class GPin : public GPIO
{
    public:
        GPin(int inPinNumber) : GPIO(inPinNumber, GPIO::IN) { }
        virtual ~GPin() { }

        std::string value()
        {
            std::stringstream ss;
	    ss << "/sys/class/gpio/gpio" << mPinNumber << "/value"; 

	    std::ifstream file(ss.str().c_str());

	    std::string txt;

	    if (file)
            {
                file >> txt;
                file.close();
            }
            else
	    {
                std::cout << " OPERATION FAILED: Unable to open file " << ss.str() << std::endl;
	        std::cout << " !!! MUST RUN AS ROOT to acess /sys/class/gpio/" << std::endl;
	    }

	    return txt;
        }
};

} /* namespace thermostat */

#endif /* _GPIN_HPP_ */
