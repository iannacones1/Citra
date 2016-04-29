#include "Interfaces/IThermostatDisplay.h"
#include "create_module_macro.h"

#include "GPout.hpp"

namespace thermostat {

class SimpleLedDisplay : public Interfaces::IThermostatDisplay
{
    public:
        SimpleLedDisplay() : Interfaces::IThermostatDisplay(),
                             mainLed(MainLedPin),
                             redLed(RedLedPin),
                             greenLed(GreenLedPin),
                             blueLed(BlueLedPin)
        {
	    mainLed.on();
        }

        virtual ~SimpleLedDisplay()
        {
	    mainLed.off();
        }

        virtual void display(bool inOn, float /* inSetPoint */, float /* inCurrentTemp */, Interfaces::Control inControlAction)
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
      CONFIGURABLE
      (
	(int) MainLedPin,
	(int) RedLedPin,
	(int) GreenLedPin,
	(int) BlueLedPin
      )
      INITIALIZE(SimpleLedDisplay);

      GPout mainLed;
      GPout redLed;
      GPout greenLed;
      GPout blueLed;

};

MODULE(Interfaces::IThermostatDisplay, SimpleLedDisplay);

} /* namespace thermostat */
