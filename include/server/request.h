#pragma once
#include <vector>
#include <string>
#include <arpa/inet.h>



/**
 * @namespace RequestHelper
 * @brief A helper namespace for parsing HTTP requests.
 */

/**
 * @typedef requestInfo
 * @brief A type alias for a 2D vector of strings, representing parsed request information.
 */

/**
 * @fn requestInfo ParseRequest(const std::string& buffer)
 * @brief Parses the given HTTP request buffer into structured request information.
 * @param buffer The raw HTTP request as a string.
 * @return A 2D vector of strings containing the parsed request information.
 */

/**
 * @fn requestInfo ParseRequestType(const std::string& buffer)
 * @brief Parses the type of the given HTTP request buffer.
 * @param buffer The raw HTTP request as a string.
 * @return A 2D vector of strings containing the parsed request type information.
 */
namespace RequestHelper {
    typedef std::vector<std::vector<std::string>> requestInfo;

    requestInfo ParseRequest(const std::string& buffer);
    requestInfo ParseRequestType(const std::string& buffer);

    struct RequestHeaders {
        std::string Accept;
        std::string UserAgent;
        std::string Authorization;
        std::string ContentType;
        std::string Cookie;
    };

    class Request {
    public:
        int RequestMethod;
        std::string Path;
        sockaddr_in Source_Address;
        std::string body;
    };
}