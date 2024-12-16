#include "../../include/server/request.h"

RequestHelper::requestInfo RequestHelper::ParseRequest(const std::string& buffer) {
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

RequestHelper::requestInfo RequestHelper::ParseRequestType(const std::string& buffer) {
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