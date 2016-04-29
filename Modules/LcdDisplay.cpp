#include <iostream>
#include <iomanip>
#include <string>

#include "Interfaces/IThermostatDisplay.h"
#include "create_module_macro.h"

#include "GPlcd.hpp"

namespace thermostat {

class LcdDisplay : public Interfaces::IThermostatDisplay
{
    public:
        LcdDisplay() : Interfaces::IThermostatDisplay(),
                       mGPlcd(26, 19, 21, 20, 16, 12)
        { }

        virtual ~LcdDisplay() { }

        virtual void display(bool inOn, float inSetPoint, float inCurrentTemp, Interfaces::Control inControlAction)
        {
            std::stringstream ss;
	    ss << toString(inCurrentTemp) << "|";
	    ss << toString(inSetPoint) << "|";

	    if (inOn)
            {
                switch (inControlAction)
                {
                    case Interfaces::STAY : { ss << "HOLD"; break; }
                    case Interfaces::HEAT : { ss << "HEAT"; break; }
                    case Interfaces::COOL : { ss << "COOL"; break; }
                    default : { ss << "????"; }
                }
            }
            else
	    {
		ss << "----";
	    }

            mGPlcd.setTextLine1("Temp |Goal |Act ");
            mGPlcd.setTextLine2(ss.str());
        }

    protected:
        std::string toString(float inVal) const
        {
            std::stringstream ss;
            ss << std::fixed << std::setprecision(2) << std::setw(5) << inVal;
	    return ss.str().substr(0,5);
        }
        CONFIGURABLE
        (
            (int) LCD_RS,
            (int) LCD_E,
            (int) LCD_D4,
            (int) LCD_D5,
            (int) LCD_D6,
            (int) LCD_D7
        )
    //      INITIALIZE(LcdDisplay);
  
        GPlcd mGPlcd;
};

MODULE(Interfaces::IThermostatDisplay, LcdDisplay);

} /* namespace thermostat */
