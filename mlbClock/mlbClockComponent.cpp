#include "mlbClockComponent.h"

#include <iomanip>
#include <unistd.h>

namespace Citra { namespace mlbClock {

static const std::string DATA_CACHE = "currentImage.bin";

mlbClockComponent::mlbClockComponent()
 : DataGrabber("./lib/XmlDataGrabber.so"), // DEFAULT
   ImageBuilder("./lib/CairoMlbImageBuilder.so"),
   DisplayModule("./lib/EinkDisplayModule.so"),
   mDataGrabber(DataGrabber),
   mImageBuilder(ImageBuilder),
   mDisplay(DisplayModule)
{ }

mlbClockComponent::~mlbClockComponent() { }

void mlbClockComponent::update()
{
    std::vector<mlbGame> aGameVector = mDataGrabber->getGames(TEAM);

    Citra::Display::ImageBuffer aImgBuf = mImageBuilder->buildImage(TEAM, aGameVector);

    Citra::Display::ImageBuffer bImgBuf(aImgBuf.width(), aImgBuf.height());
    bImgBuf.fromFile(DATA_CACHE);

    if (aImgBuf != bImgBuf)
    {
        mDisplay->display(aImgBuf);

        aImgBuf.toFile(DATA_CACHE);
    }

}

} /* namespace mlbClock */ } /* namespace Citra */
