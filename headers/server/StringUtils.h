#include <iostream>
#include <string.h>

namespace StringUtils{
    /*
    * Check if a string contains a substring
    Example params: 
    char* string: "GET"
    char* substring: ['G', 'E', 'T']
    */
    bool Contains(char* string, char* substring){
        int strLength = strlen(string);
        for (int i = 0; i < strLength; i++) {
            if (string[i] == substring[0]){
                bool found = true;
                int subStrLength = strlen(substring);
                std::cout << subStrLength << std::endl;
                for (int j = 0; j < subStrLength; j++){
                    if (i+j > strLength) return false;
                    std::cout << string[i+j] << " " << substring[j] << std::endl;
                    if (string[i+j] != substring[j]){
                        found = false;
                        break;
                    }
                }
                if (found){
                    return true;
                }
            }
        }
        return false;
    }

}