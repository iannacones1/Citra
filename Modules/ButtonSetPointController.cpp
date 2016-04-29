#include <unistd.h>
#include <thread>

#include "Interfaces/ISetPointController.h"
#include "create_module_macro.h"

#include "GPin.hpp"

namespace thermostat {

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
        GPin mOnOffButton;
        std::string mUValue;
        GPin mUpButton;
        std::string mDValue;
        GPin mDownButton;

};

MODULE(Interfaces::ISetPointController, TestSetPointController);

} /* namespace thermostat*/
