#ifndef _HTTP_CLIENT_H_
#define _HTTP_CLIENT_H_

#include <string>

namespace Citra { namespace Http {

    // make a Synchronous Http request
    //
    //
    // version 10 = 1.0; 11 = 1.1
    std::string SynchronousGet(const std::string& inHost,
                               const std::string& inTarget,
                               const std::string& inProtocol = "http",
                               int                inVersion = 11);

} /* namespace Http*/ } /* namespace Citra */

#endif /* _HTTP_CLIENT_H_ */
