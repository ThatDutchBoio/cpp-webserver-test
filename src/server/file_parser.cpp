#include "../../include/server/file_parser.h"
#include <fstream>
#include <sstream>

std::string file_parser::FileParser::GetHTMLPage(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        return "<h1>404 Not Found</h1>";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

std::string file_parser::FileParser::GetFileContents(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        return "<h1>404 Not Found</h1>";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}