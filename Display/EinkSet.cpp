#include <iostream>

#include <Display/EinkDisplay.h>

// sudo ./EinkSet $'\x00'
// sudo ./EinkSet $'\x33'

int main(int argc, char* argv[])
{
    std::cout << "Running " << argv[0] << std::endl;

    Citra::Display::EinkDisplay aDisplay;

    if (!aDisplay.initialize())
    {
        std::cerr << "Failed to initialize EinkDiplay" << std::endl;
        return -1;
    }

    for (int i = 1; i < argc; i++)
    {
        aDisplay.set(*(unsigned char*)argv[i]);
    }

    std::cout << "(DONE)" << std::endl;
    return 0;
}
