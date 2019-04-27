#ifndef _MODULE_HPP_
#define _MODULE_HPP_

#include <iostream>
#include <string>
#include <memory>

#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#include <boost/shared_ptr.hpp>

namespace Citra {

template<class I>
class Module
{
    public:
        Module() : mHandle(), mPtr() {}

        Module(const std::string& inLib) : mHandle(), mPtr()
        {
            if (inLib.empty()) { return; }

            auto libClose = [](void* inHandle) { if (inHandle) dlclose(inHandle); };

	        // http://www.linuxjournal.com/article/3687
	        // http://www.dwheeler.com/program-library/Program-Library-HOWTO/x172.html
	        mHandle.reset(dlopen(inLib.c_str(), RTLD_NOW), libClose);

	        char* err = dlerror();

            if (mHandle)
	        {
                I* (*mkr)();
                mkr = (I* (*)())dlsym(mHandle.get(), "create_module");

                err = dlerror();

                if (mkr && err == NULL)
                {
                    I* newptr = (mkr)();

                    mPtr.reset(newptr);
                }
                else
                {
                    std::cerr << "Issue during dlsym(" << inLib << ") ERROR: " << err << std::endl;
                }
	        }
            else
            {
                std::cerr << "Issue during dlopen(" << inLib << ") ERROR: " << err << std::endl;
            }
        }

        virtual ~Module() { }

        I* operator->() { return mPtr.get(); }
        
    private:
        boost::shared_ptr<void> mHandle;
        boost::shared_ptr<I> mPtr;

};

} /* namespace Citra */

#endif /* _MODULE_H_ */

