#pragma once
#include <vector>
#include <string>
#include <arpa/inet.h>

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

namespace RequestHelper {
    typedef std::vector<std::vector<std::string>> requestInfo;

    requestInfo ParseRequest(const std::string& buffer);
    requestInfo ParseRequestType(const std::string& buffer);
}