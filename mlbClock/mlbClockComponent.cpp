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

        size_t focalGame = games.size() - 1;

        for (; focalGame > 0; focalGame--)
        {

            if (games.at(focalGame).status == "Preview" ||
                games.at(focalGame).status == "In Progress" ||
                games.at(focalGame).status == "Delay")
            {
                break;
            }
        }

        mlbGame cGame = games.at(focalGame);

        Citra::Display::ImageBuffer aImgBuf = mImageBuilder->buildImage(TEAM, games);

        mDisplay->display(aImgBuf);

        sleep(cGame.status != "In Progress" ? 60 : 10);
    }
}

} /* namespace mlbClock */ } /* namespace Citra */
