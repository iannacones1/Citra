#include <time.h>

#include <GPIO/GPout.hpp>

#include <Thermostat/Interfaces/IThermalController.h>
#include <Module/create_module_macro.h>

namespace Citra { namespace Thermostat {

class PowerSwitchTailController : public Interfaces::IThermalController
{
    public:
        PowerSwitchTailController()
          : Interfaces::IThermalController(),
	        mLastChange(time(NULL)),
	        mCurrentState(false),
	        mNormalyOpen(false),
            mOut(24)
        {
	        mOut.setOn(!mNormalyOpen);
        }

        virtual ~PowerSwitchTailController()
        {
	        mOut.setOn(!mNormalyOpen);
        }

        virtual void heat()
        {
	        setState(true);
        }

        virtual void cool()
        {
	        setState(false);
        }

        virtual void stay()
        {
	        setState(false);
        }

    protected:
        void setState(bool inState)
        {
	        time_t now = time(NULL);

	        if (inState != mCurrentState && difftime(now, mLastChange) >= 2) // don't change faster then every 2 secs
	        {
                mOut.setOn((mNormalyOpen ? inState : !inState));
		        mLastChange = now;
		        mCurrentState = inState;
	        }
        }

        time_t mLastChange;
        bool mCurrentState;
        bool mNormalyOpen;
        GPIO::GPout mOut;
};

MODULE(Interfaces::IThermalController, PowerSwitchTailController)

} /* namespace Thermostat*/ } /* namespace Citra */


