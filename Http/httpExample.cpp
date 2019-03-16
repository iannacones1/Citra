#include <Http/httpClient.h>

#include <cstdlib>
#include <iostream>
#include <string>

#include <boost/lexical_cast.hpp>

// Performs an HTTP GET and prints the response
int main(int argc, char** argv)
{
    // Check command line arguments.
    if (argc < 3)
    {
        std::cerr <<
                "Usage: " << argv[0] << " <host> <target> [<protocol http(default)>] [<version: 10 or 11(default)>]\n" <<
                "Example:\n" <<
                "    " << argv[0] << " www.example.com /\n" <<
                "    " << argv[0] << " www.example.com / https 10\n";
        return EXIT_FAILURE;
    }

    std::string aHost     = argv[1];
    std::string aTarget   = argv[2];
    std::string aProtocol = (argc >= 4 ? argv[3] : "http");
    int         aVersion  = (argc >= 5 ? boost::lexical_cast<int>(argv[4]) : 11);

    std::string httpResponse = Citra::Http::SynchronousGet(aHost, aTarget, aProtocol, aVersion);

    std::cout << httpResponse << std::endl;

    return EXIT_SUCCESS;
}

//]
