#include "../../include/server/request.h"

/**
 * @brief Parses the HTTP request from the given buffer string.
 *
 * This function takes a raw HTTP request string and parses it into a structured format.
 * It splits the request into lines and stores each line in a vector of strings.
 * Each line is then added to a vector representing the entire request.
 *
 * @param buffer The raw HTTP request string to be parsed.
 * @return A vector of vectors of strings, where each inner vector represents a line in the request.
 */
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

/**
 * @brief Parses the request type from the given buffer string.
 *
 * This function processes the input buffer string and extracts the request type
 * information. It splits the buffer into words based on spaces and organizes
 * them into a vector of vectors of strings.
 *
 * @param buffer The input string containing the request data.
 * @return A vector of vectors of strings representing the parsed request type.
 */
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