#include <iostream>

#include <Module/create_module_macro.h>

#include <Display/Interfaces/iBufferDisplay.h>
#include <Display/EinkDisplay.h>

namespace Citra { namespace Display {

class EinkDisplayModule : public Interfaces::iBufferDisplay
{
    public:
        EinkDisplayModule()
         : Interfaces::iBufferDisplay(),
           mCurrentBuffer(EinkDisplay::WIDTH, EinkDisplay::HEIGHT, 0x33),
           mDisplay()
        {
            if (!mDisplay.initialize())
            {
                std::cerr << "e-Paper init failed" << std::endl;
                throw;
            }
        }

        virtual ~EinkDisplayModule() { }

        virtual void display(const ImageBuffer& inBuffer)
        {
            // filtering logic
            if (inBuffer == mCurrentBuffer)
            {
                return;
            }

            mDisplay.display(inBuffer);

            mCurrentBuffer = inBuffer;
        }

        Citra::Display::ImageBuffer mCurrentBuffer;
        EinkDisplay mDisplay;
};

MODULE(Interfaces::iBufferDisplay, EinkDisplayModule)

} /* namespace Display*/ } /* namespace Citra */
