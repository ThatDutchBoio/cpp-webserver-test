#ifndef FILE_PARSER_H

#define FILE_PARSER_H



#include <string>



/**
 * @class FileParser
 * @brief A class responsible for parsing files.
 *
 * This class provides static methods to parse and retrieve content from files.
 */

/**
 * @brief Retrieves the content of an HTML page from the specified file path.
 *
 * This static method reads the content of the file located at the given path
 * and returns it as a string.
 *
 * @param path The file path to the HTML page.
 * @return A string containing the content of the HTML page.
 */

namespace file_parser {
    class FileParser {
        public:
            static std::string GetHTMLPage(const std::string& path);
            static std::string GetFileContents(const std::string& path);
    };

}



#endif // FILE_PARSER_H