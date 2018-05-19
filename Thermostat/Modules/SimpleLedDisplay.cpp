#include <Thermostat/Interfaces/IThermostatDisplay.h>
#include <Module/create_module_macro.h>

#include <GPIO/GPout.hpp>
#include <Configurable/Configurable.hpp>

namespace Citra { namespace Thermostat {

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
      INITIALIZE(SimpleLedDisplay)

      GPIO::GPout mainLed;
      GPIO::GPout redLed;
      GPIO::GPout greenLed;
      GPIO::GPout blueLed;

};

MODULE(Interfaces::IThermostatDisplay, SimpleLedDisplay)

} /* namespace Thermostat*/ } /* namespace Citra */
