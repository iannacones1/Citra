#include "../Interfaces/IThermostatDisplay.h"
#include "create_module_macro.h"

#include "../GPIO.hpp"

namespace thermostat {

class SimpleLedDisplay : public Interfaces::IThermostatDisplay
{
    public:
        SimpleLedDisplay()
          : Interfaces::IThermostatDisplay(),
            mainLed(18),
            redLed(17),
            greenLed(27),
            blueLed(22)
        {
	    mainLed.on();
        }

        virtual ~SimpleLedDisplay()
        {
	    mainLed.off();
        }

        virtual void display(bool inOn, float inSetPoint, float inCurrentTemp, Interfaces::Control inControlAction)
        {
            redLed.off();
            greenLed.off();
            blueLed.off();

            if (!inOn) { return; }

            switch (inControlAction)
            {
                case Interfaces::STAY : { greenLed.on(); break; }
                case Interfaces::HEAT : { redLed.on();   break; }
                case Interfaces::COOL : { blueLed.on();  break; }
	    }
	}

    protected:
      GPIO mainLed;
      GPIO redLed;
      GPIO greenLed;
      GPIO blueLed;

};

MODULE(Interfaces::IThermostatDisplay, SimpleLedDisplay);

} /* namespace thermostat */
