#ifndef _E_INK_DISPLAY_H_
#define _E_INK_DISPLAY_H_

#include "ImageBuffer.hpp"

namespace Citra { namespace Display {

class EinkDisplay
{
  public:
    EinkDisplay();
    virtual ~EinkDisplay();

    bool initialize();
    void display(const ImageBuffer& inImageBuffer);

  protected:
    void waitUntilIdle();
    void reset();
    void sendCommand(unsigned char command);
    void sendData(unsigned char data);
    void sleep();

    Citra::Display::ImageBuffer mCurrentBuffer;
};

} /* namespace Display*/ } /* namespace Citra */

#endif /* _E_INK_DISPLAY_H_ */
