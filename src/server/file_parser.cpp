#include "../../include/server/file_parser.h"
#include <fstream>
#include <sstream>
#include <filesystem>

std::string file_parser::FileParser::GetHTMLPage(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        return "<h1>404 Not Found</h1>";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

/**
 * @brief Reads the contents of a file and returns it as a string.
 *
 * This function attempts to open the file at the specified path and read its contents.
 * If the file cannot be opened, it returns a "404 Not Found" HTML message.
 *
 * @param path The path to the file to be read.
 * @return A string containing the contents of the file, or a "404 Not Found" message if the file cannot be opened.
 */
std::string file_parser::FileParser::GetFileContents(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        return "<h1>404 Not Found</h1>";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

/**
 * @brief Checks if the given filename has the specified extension.
 * 
 * This function compares the end of the filename with the provided extension
 * to determine if the filename ends with that extension.
 * 
 * @param filename The name of the file to check.
 * @param extension The extension to check for.
 * @return true If the filename ends with the specified extension.
 * @return false If the filename does not end with the specified extension.
 */
bool file_parser::FileParser::IsFileOfType(std::string filename, std::string extension){
    return std::filesystem::path(filename).extension() == extension;
}