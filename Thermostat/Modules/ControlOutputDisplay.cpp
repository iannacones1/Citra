#include <iostream>
#include <iomanip>
#include <list>
#include <string>

#include <Thermostat/Interfaces/IThermostatDisplay.h>
#include <Module/create_module_macro.h>

namespace Citra { namespace Thermostat {

class ControlOutputDisplay : public Interfaces::IThermostatDisplay
{
    public:
        ControlOutputDisplay() : Interfaces::IThermostatDisplay(),
	                         mWait(),
                                 mIter()
        {
	        mWait.push_back("|");
	        mWait.push_back("/");
	        mWait.push_back("-");
	        mWait.push_back("\\");

	        mIter = mWait.begin();

            std::cout << "+-----+--------+--------+--------+" << std::endl;
	        std::cout << "| ON? |  Temp  |  Goal  | Action |" << std::endl;
            std::cout << "+-----+--------+--------+--------+" << std::endl;
        }

        virtual ~ControlOutputDisplay()
        {
            std::cout << std::endl;
            std::cout << "+-----+--------+--------+--------+" << std::endl;
        }

        virtual void display(bool inOn, float inSetPoint, float inCurrentTemp, Interfaces::Control inControlAction)
        {
	        std::cout << "\r";
	        std::cout << "| " << (inOn ? "ON " : "OFF") << " | ";
	        std::cout << std::fixed << std::setprecision(2) << std::setw(6) << inCurrentTemp << " | ";
	        std::cout << std::fixed << std::setprecision(2) << std::setw(6) << inSetPoint << " |  ";

	        if (inOn)
	        {
                switch (inControlAction)
                {
                    case Interfaces::STAY : { std::cout << "STAY"; break; }
                    case Interfaces::HEAT : { std::cout << "HEAT"; break; }
                    case Interfaces::COOL : { std::cout << "COOL"; break; }
                    default :  { std::cout << "????"; }
	            }
            }
	        else
	        {
                std::cout << "----";
	        }

	        std::cout << "  |";
	        std::cout << *mIter << "\r" << std::flush;

	        mIter++;
	        if (mIter == mWait.end()) mIter = mWait.begin();
	    }

    protected:
        std::list<std::string> mWait;
        std::list<std::string>::iterator mIter;

};

MODULE(Interfaces::IThermostatDisplay, ControlOutputDisplay)

} /* namespace Thermostat*/ } /* namespace Citra */
