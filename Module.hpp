#ifndef _MODULE_HPP_
#define _MODULE_HPP_

#include <string>
#include <memory>

#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#include <boost/shared_ptr.hpp>

template<class I>
class Module
{
    public:
        Module() : mHandle(), mPtr() {}

        Module(const std::string& inLib) : mHandle(), mPtr()
        {
            char* err;

	    // http://www.linuxjournal.com/article/3687
	    // http://www.dwheeler.com/program-library/Program-Library-HOWTO/x172.html
	    mHandle.reset(dlopen(inLib.c_str(), RTLD_NOW), dlclose);

            err = dlerror();
            if (!mHandle)
	    {
                std::cerr << "Issue during dlopen(" << inLib << ") ERROR: " << err << std::endl;
                throw;
	    }

            I* (*mkr)();
            mkr = (I* (*)())dlsym(mHandle.get(), "create_module");

            err = dlerror();
	    if (!mkr || err != NULL)
	    {
	        std::cerr << "Issue during dlsym(" << inLib << ") ERROR: " << err << std::endl;
                throw;
	    }

            I* newptr = (mkr)();

            mPtr.reset(newptr);
        }

        virtual ~Module() { }

        I* operator->() { return mPtr.get(); }
        
    private:
        boost::shared_ptr<void> mHandle;
        boost::shared_ptr<I> mPtr;

};

#endif /* _MODULE_H_ */

