#ifndef _i_BUFFER_DISPLAY_H_
#define _i_BUFFER_DISPLAY_H_

#include <Display/ImageBuffer.hpp>

namespace Citra { namespace Display { namespace Interfaces {

class iBufferDisplay
{
    public:
        iBufferDisplay() { }
        virtual ~iBufferDisplay() { }

        virtual void display(const ImageBuffer& inBuffer) = 0;

};

} /* namespace Interfaces*/ } /* namespace Display */ } /* namespace Citra */

#endif /* _i_BUFFER_DISPLAY_H_ */
