#ifndef _EXCEPTION_HPP_
#define _EXCEPTION_HPP_

#include <iostream>
#include <sstream>
#include <stdexcept>

namespace Citra { namespace Language {

class Exception : public std::runtime_error
{
    public:
        Exception(const std::string& inError) : std::runtime_error(inError) { }

        Exception(const std::stringstream& inError) : std::runtime_error(inError.str())
        {
            std::cerr << inError.str() << std::endl;
        }

        virtual ~Exception() { }
};

} /* namespace Language*/ } /* namespace Citra */

#endif /* _EXCEPTION_HPP_ */
