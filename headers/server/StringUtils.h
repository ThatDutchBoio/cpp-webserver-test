#include <iostream>
#include <string>

namespace StringUtils {
    /*
    * Check if a string contains a substring
    Example params: 
    std::string string: "GET"
    std::string substring: "GET"
    */
    bool Contains(const std::string& str, const std::string& substr) {
        return str.find(substr) != std::string::npos;
    }
}