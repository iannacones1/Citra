#ifndef _DEMANGLER_HPP_
#define _DEMANGLER_HPP_

#include <string>
#include <cxxabi.h>

namespace Citra { namespace Language {

// Dont't like the way the demangler turns "std::string" into "std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >"?
// use this macro to specialize the demangle() method
#define OVERRIDE_DEMANGLE(type) \
template<> inline std::string Demangler::demangle<type>() { return #type; }

class Demangler
{
    public:
	    template<class T>
        static std::string demangle()
	    {
	        int  status = 0;

	        char* demangled_name = abi::__cxa_demangle(typeid(T).name(), 0, 0, &status);

	        if (status) { std::cerr << __func__ << " error: " << status << std::endl; }

            std::string result(demangled_name);

	        free(demangled_name);

	        return result;
        }

	    template<class T>
        static std::string demangle(const T& /* inClass */) { return demangle<T>(); }

	    template<class T>
        static std::string demangle(const std::list<T>& /* inClass */)
	    { return "std::list<" + demangle<T>() + ">"; }

    private:
	    Demangler();
};

OVERRIDE_DEMANGLE(std::string)

} /* namespace Language*/ } /* namespace Citra */

#endif /* _DEMANGLER_HPP_ */
