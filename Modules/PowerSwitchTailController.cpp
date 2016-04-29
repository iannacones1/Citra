#include <time.h>

#include "GPout.hpp"

#include "Interfaces/IThermalController.h"
#include "create_module_macro.h"

namespace thermostat {

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
        GPout mOut;

};

MODULE(Interfaces::IThermalController, PowerSwitchTailController);

} /* namespace thermostat */


