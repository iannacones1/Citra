#ifndef _E_INK_DISPLAY_H_
#define _E_INK_DISPLAY_H_

#include "ImageBuffer.hpp"

namespace Citra { namespace Display {

class EinkDisplay
{
  public:
    static const int WIDTH  = 640;
    static const int HEIGHT = 384;

    EinkDisplay();
    virtual ~EinkDisplay();

    bool initialize();
    void display(const ImageBuffer& inImageBuffer);

    void set(unsigned char inChar, int inNum);
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
