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

        size_t focalGame = (games.at(2).status == "Preview" ? 1 : 2);

        mlbGame cGame = games.at(focalGame);

        Citra::Display::ImageBuffer aImgBuf = mImageBuilder->buildImage(TEAM, games);

        mDisplay->display(aImgBuf);

        sleep(cGame.status != "In Progress" ? 60 : 1);
    }
}

} /* namespace mlbClock */ } /* namespace Citra */
