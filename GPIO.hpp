#ifndef _GPIO_HPP_
#define _GPIO_HPP_

#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

namespace thermostat {

// http://hertaville.com/introduction-to-accessing-the-raspberry-pis-gpio-in-c.html
class GPIO
{
    public:
        GPIO(int inPinNumber) : mPinNumber(inPinNumber)
        {
            std::cout << __func__ << " " << mPinNumber << std::endl;
            this->write("/sys/class/gpio/export", mPinNumber);

            std::stringstream ss;
            ss << "/sys/class/gpio/gpio" << mPinNumber << "/direction"; 
            this->write(ss.str(), "out");
        }

        virtual ~GPIO()
        {
            this->off();
            this->write("/sys/class/gpio/unexport", mPinNumber);
        }

        void on()
        {
	  std::stringstream ss;
	  ss << "/sys/class/gpio/gpio" << mPinNumber << "/value"; 
	  this->write(ss.str(), "1");
        }

        void off()
        {
	  std::stringstream ss;
	  ss << "/sys/class/gpio/gpio" << mPinNumber << "/value"; 
	  this->write(ss.str(), "0");
        }

    protected:
        template <typename T>
        void write(const std::string& inFileName, const T& inValue) const
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


  int mPinNumber;

};

} /* namespace thermostat */

#endif /* _GPIO_HPP_ */
