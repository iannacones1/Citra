#ifndef _GPIO_HPP_
#define _GPIO_HPP_

#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

namespace Citra { namespace GPIO {

// http://hertaville.com/introduction-to-accessing-the-raspberry-pis-gpio-in-c.html
class GPIObase
{
    public:
        enum DIRECTION
        {
            OUT,
            IN
        };

        explicit GPIObase(int inPinNumber, const DIRECTION& inDirection) : mPinNumber(inPinNumber)
        {
            this->write("/sys/class/gpio/export", mPinNumber);

            std::stringstream ss;
            ss << "/sys/class/gpio/gpio" << mPinNumber << "/direction"; 

	        std::string aDirection = (inDirection == OUT ? "out" : "in");

            this->write(ss.str(), aDirection);
        }

        virtual ~GPIObase()
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
	            std::cerr << " OPERATION FAILED: Unable to open file " << inFileName << std::endl;
	            std::cerr << " !!! MUST RUN AS ROOT to acess /sys/class/gpio/" << std::endl;
	            return;
	        }

            aFileStream << inValue;
            aFileStream.close();
            
        }

        int mPinNumber;

};

} /* namespace GPIO */ } /* namespace Citra */

#endif /* _GPIO_HPP_ */
