#ifndef _EXCEPTION_HPP_
#define _EXCEPTION_HPP_

#include <sstream>
#include <stdexcept>

#define THROW_RUNTIME_EXCEPTION(msg)       \
{                                          \
    std::stringstream rtess;               \
    rtess << msg;                          \
    throw std::runtime_error(rtess.str()); \
}

namespace Citra { namespace Language {

} /* namespace Language*/ } /* namespace Citra */

#endif /* _EXCEPTION_HPP_ */
