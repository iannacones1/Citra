#ifndef _MODULE_HPP_
#define _MODULE_HPP_

#include <string>
#include <memory>

#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>

template<class I>
class Module
{
    public:
        Module(const std::string& inLib) : mHandle(), mPtr()
        {
            std::cout << __func__ << " " << inLib << std::endl;

	    // http://www.linuxjournal.com/article/3687
	    // http://www.dwheeler.com/program-library/Program-Library-HOWTO/x172.html
            mHandle = dlopen(inLib.c_str(), RTLD_NOW);

            if (!mHandle)
	    {
                std::cerr << "Issue during dlopen(" << inLib << ") ERROR: " << dlerror() << std::endl;
                throw;
	    }

            I* (*mkr)();
            mkr = (I* (*)())dlsym(mHandle, "create_module");

	    // TODO: this error handleing for dlsym doesn't work; but something like it should be here
            //char* error = dlerror();
	    //if ((error = dlerror()) != NULL)
	    //{
            //    std::cerr << "Issue during dlsym(" << inLib << ") ERROR: " << error << std::endl;
            //    throw;
	    //}

            I* newptr = (mkr)();

            mPtr = std::unique_ptr<I>(newptr);
        }

        virtual ~Module()
        {
	    mPtr.reset();
            dlclose(mHandle);
        }

        I* get() { return mPtr.get(); }

    private:
        void* mHandle;
        std::unique_ptr<I> mPtr;

};

#endif /* _MODULE_H_ */

