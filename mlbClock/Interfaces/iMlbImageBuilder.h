#ifndef _i_MLB_IMAGE_BUILDER_H_
#define _i_MLB_IMAGE_BUILDER_H_

#include <mlbClock/mlbData.hpp>

#include <Display/ImageBuffer.hpp>

#include <list>
#include <string>

namespace Citra { namespace mlbClock { namespace Interfaces {

class iMlbImageBuilder
{
    public:
        virtual ~iMlbImageBuilder() { }

        virtual Display::ImageBuffer buildImage(const std::string& inTeam, const std::vector<mlbGame>& inGameList) = 0;

    protected:
        iMlbImageBuilder() { }
};

} /* namespace Interfaces*/ } /* namespace mlbClock */ } /* namespace Citra */

#endif /* _i_MLB_IMAGE_BUILDER_H_ */
