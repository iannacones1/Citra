#ifndef _MLB_CLOCK_COMPONENT_H_
#define _MLB_CLOCK_COMPONENT_H_

#include <mlbClock/Interfaces/iMlbDataGrabber.h>
#include <mlbClock/Interfaces/iMlbImageBuilder.h>
#include <Display/Interfaces/iBufferDisplay.h>
#include <Module/Module.hpp>
#include <Configurable/Configurable.hpp>

#include <string>

namespace Citra { namespace mlbClock {

class mlbClockComponent
{
    public:
	    mlbClockComponent();
        virtual ~mlbClockComponent();

        void update();

    protected:
        CONFIGURABLE
        (
            (std::string) DataGrabber,
            (std::string) ImageBuilder,
            (std::string) DisplayModule,
            (std::string) TEAM,
            (bool)        ForceUpdate
        )

        INITIALIZE(mlbClockComponent)

        Module<Interfaces::iMlbDataGrabber> mDataGrabber;
        Module<Interfaces::iMlbImageBuilder> mImageBuilder;
        Module<Display::Interfaces::iBufferDisplay> mDisplay;
};

} /* namespace mlbClock */ } /* namespace Citra */

#endif /* _MLB_CLOCK_COMPONENT_H_ */
