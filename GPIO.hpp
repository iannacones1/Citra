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
        enum DIRECTION
        {
            OUT,
            IN
        };

        explicit GPIO(int inPinNumber, const DIRECTION& inDirection) : mPinNumber(inPinNumber)
        {
            this->write("/sys/class/gpio/export", mPinNumber);

            std::stringstream ss;
            ss << "/sys/class/gpio/gpio" << mPinNumber << "/direction"; 

	    std::string aDirection = (inDirection == OUT ? "out" : "in");

            this->write(ss.str(), aDirection);
        }

        virtual ~GPIO()
        {
            this->write("/sys/class/gpio/unexport", mPinNumber);
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
