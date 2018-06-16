#include <iostream>

#include <Module/create_module_macro.h>
#include <Display/Interfaces/iBufferDisplay.h>

namespace Citra { namespace Display {

class TestDisplayModule : public Interfaces::iBufferDisplay
{
    public:
        TestDisplayModule() : Interfaces::iBufferDisplay()
        { }

        virtual ~TestDisplayModule() { }

        virtual void display(const ImageBuffer& /* inBuffer */)
        {
            std::cout << "TestDisplayModule::" << __func__ << std::endl;
        }
};

MODULE(Interfaces::iBufferDisplay, TestDisplayModule)

} /* namespace Display*/ } /* namespace Citra */
