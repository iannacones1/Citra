// Based off:
// https://github.com/boostorg/beast
// Example: HTTP client, synchronous

#include <Http/httpClient.h>

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <cstdlib>
#include <iostream>
#include <string>

std::string Citra::Http::SynchronousGet(const std::string& inHost,
                                        const std::string& inTarget,
                                        const std::string& inProtocol /* = "http" */,
                                        int                inVersion  /* = 10     */)
{
    std::string aResponseStr;

    try
    {
        // The io_context is required for all I/O
        boost::asio::io_context aIoContext;

        // These objects perform our I/O
        boost::asio::ip::tcp::resolver aResolver(aIoContext);
        boost::beast::tcp_stream aStream(aIoContext);

        boost::asio::ip::tcp::resolver::query aQuery(inHost, inProtocol);

        // Look up the domain name
        //boost::asio::ip::tcp::resolver::iterator aResults = aResolver.resolve(aQuery);
        auto const aResults = aResolver.resolve(aQuery);

        // Make the connection on the IP address we get from a lookup
        aStream.connect(aResults);

        // Set up an HTTP GET request message
        boost::beast::http::request<boost::beast::http::string_body> aRequest{boost::beast::http::verb::get, inTarget, inVersion};
        aRequest.set(boost::beast::http::field::host, inHost);
        aRequest.set(boost::beast::http::field::user_agent, BOOST_BEAST_VERSION_STRING);

        // Send the HTTP request to the remote host
        boost::beast::http::write(aStream, aRequest);

        // This buffer is used for reading and must be persisted
        boost::beast::flat_buffer aBuffer;

        // Declare a container to hold the response
        boost::beast::http::response<boost::beast::http::dynamic_body> aResponse;

        // Receive the HTTP response
        boost::beast::http::read(aStream, aBuffer, aResponse);

        // Write the message to string
        aResponseStr = boost::beast::buffers_to_string(aResponse.body().data());

        // Gracefully close the socket
        boost::beast::error_code aError;
        aStream.socket().shutdown(boost::asio::ip::tcp::socket::shutdown_both, aError);

        // not_connected happens sometimes
        // so don't bother reporting it.
        //
        if (aError && aError != boost::beast::errc::not_connected)
        {
            throw boost::beast::system_error{aError};
        }
        // If we get here then the connection is closed gracefully
    }
    catch (const std::exception& aException)
    {
        std::cerr << "Error: " << aException.what() << std::endl;
        return "";
    }

    return aResponseStr;
}
