#ifndef _GP_OUT_HPP_
#define _GP_OUT_HPP_

#include <sstream>

#include "GPIO.hpp"

namespace thermostat {

// http://hertaville.com/introduction-to-accessing-the-raspberry-pis-gpio-in-c.html
class GPout : public GPIO
{
    public:
        GPout(int inPinNumber) : GPIO(inPinNumber, GPIO::OUT) { }
        virtual ~GPout() { this->off(); }

        void on() { this->setValue("1"); }
        void off() { this->setValue("0"); }

        void setOn(bool inValue)
        {
	  this->setValue((inValue ? "1" : "0"));
	}

    protected:
        void setValue(const std::string& inValue)
        {
	    std::stringstream ss;
	    ss << "/sys/class/gpio/gpio" << mPinNumber << "/value"; 
	    this->write(ss.str(), inValue);
        }
};

} /* namespace thermostat */

#endif /* _GP_OUT_HPP_ */
