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

    requestInfo ParseRequest(const std::string& buffer) {
        std::vector<std::vector<std::string>> request;
        std::vector<std::string> line;
        std::string currentLine;
        for (char ch : buffer) {
            if (ch == '\n') {
                line.push_back(currentLine);
                request.push_back(line);
                line.clear();
                currentLine.clear();
            } else {
                currentLine += ch;
            }
        }
        return request;
    }

    requestInfo ParseRequestType(const std::string& buffer) {
        std::vector<std::vector<std::string>> requestType;
        std::vector<std::string> line;
        std::string currentWord;
        for (char ch : buffer) {
            if (ch == ' ') {
                line.push_back(currentWord);
                requestType.push_back(line);
                line.clear();
                currentWord.clear();
            } else {
                currentWord += ch;
            }
        }
        return requestType;
    }
}