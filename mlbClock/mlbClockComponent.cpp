#include "mlbClockComponent.h"

#include <iomanip>
#include <unistd.h>

namespace Citra { namespace mlbClock {

mlbClockComponent::mlbClockComponent()
 : mShutdown(false),
   mDataGrabber(DataGrabber),
   mImageBuilder(ImageBuilder),
   mDisplay(DisplayModule)
{ }

mlbClockComponent::~mlbClockComponent() { }

void mlbClockComponent::shutdown()
{
    std::cout << __func__ << std::endl;
    mShutdown = true;
}

void mlbClockComponent::run()
{
    while (!mShutdown)
    {
        std::vector<mlbGame> games = mDataGrabber->getGames(TEAM);

        Citra::Display::ImageBuffer aImgBuf = mImageBuilder->buildImage(TEAM, games);

        mDisplay->display(aImgBuf);

	bool inProgress = false;
        for (const mlbGame& aGame : games)
        {
            inProgress |= aGame.isUpdating();
        }

        int durationSec = (inProgress ? 5 : 60);
        std::cout << (inProgress ? "G" : "No g") << "ame in progress sleep(" << durationSec << ")" << std::endl;
        sleep(durationSec);
    }
}

} /* namespace mlbClock */ } /* namespace Citra */
