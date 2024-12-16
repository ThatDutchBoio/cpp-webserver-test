#include <iostream>
#include <fstream>

namespace FileParser{
    std::string GetHTMLPage(std::string path){
        std::ifstream HTMLFile(path); 
        std::string fileContents;
        std::string res = "";
        while (getline (HTMLFile, fileContents))  {
            res += fileContents;
        }

        HTMLFile.close();
        return res;
    }
}