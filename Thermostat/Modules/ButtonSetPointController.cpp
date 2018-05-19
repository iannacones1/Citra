#include <unistd.h>
#include <thread>

#include <Thermostat/Interfaces/ISetPointController.h>
#include <Module/create_module_macro.h>

#include <GPIO/GPin.hpp>

namespace Citra { namespace Thermostat {

class TestSetPointController : public Interfaces::ISetPointController
{
    public:
        TestSetPointController()
         : Interfaces::ISetPointController(),
           mOn(false),
	       mSetPoint(55.0),
           mOnOffButton(7),
           mUpButton(8),
           mDownButton(5)
        { }

        virtual ~TestSetPointController() { }

        virtual bool isSetPointDefined()
        { 
            std::string aValue = mOnOffButton.value();

	        if (mLastValue != aValue && aValue == "0") { mOn = !mOn; }

            mLastValue = aValue;

            return mOn;
        }

        virtual float currentSetPointFahrenheit()
        {
            std::string uValue = mUpButton.value();

	        if (/*mUValue != uValue && */ uValue == "0") { mSetPoint++; }

            mUValue = uValue;

            std::string dValue = mDownButton.value();

	        if ( /* mDValue != dValue && */ dValue == "0") { mSetPoint--; }

            mDValue = dValue;

            return mSetPoint;
        }

    protected:
        bool mOn;
        float mSetPoint;
        std::string mLastValue;
        GPIO::GPin mOnOffButton;
        std::string mUValue;
        GPIO::GPin mUpButton;
        std::string mDValue;
        GPIO::GPin mDownButton;

};

MODULE(Interfaces::ISetPointController, TestSetPointController)

} /* namespace Thermostat*/ } /* namespace Citra*/
