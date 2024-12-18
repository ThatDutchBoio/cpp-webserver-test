#include "../../include/server/static.h"
#include "../../include/server/file_parser.h"
#include "../../include/server/request.h"
#include "../../include/server/response.h"
// using namespace serve_static;
#include <filesystem>
#include <iostream>
#include <vector>
namespace fs = std::filesystem;


/**
 * @brief Constructs a Static object and initializes it with the given URL path and folder path.
 * 
 * This constructor iterates through the files in the specified folder path, determines their content type,
 * and adds them to the internal file mapping.
 * 
 * @param url_path The URL path that maps to the static files.
 * @param folder_path The filesystem path to the folder containing the static files.
 */
serve_static::Static::Static(std::string url_path, std::string folder_path){
    this->url_path = url_path;
    this->folder_path = folder_path;
    for (const auto & entry : fs::directory_iterator(folder_path)){
        std::cout << entry.path() << std::endl;
        std::cout << entry.path().filename() << std::endl;
        Enums::CONTENT_TYPE FileType = Enums::TEXT_PLAIN;
        if (file_parser::FileParser::IsFileOfType(entry.path().filename(), ".css")){
            FileType = Enums::TEXT_CSS;
        }
        if (file_parser::FileParser::IsFileOfType(entry.path().filename(), ".html")){
            FileType = Enums::TEXT_HTML;
        }
        if (file_parser::FileParser::IsFileOfType(entry.path().filename(), "json")){
            FileType = Enums::TEXT_JSON;
        }
        this->AddFileFullPath(entry.path().filename(), entry.path(), FileType);    
    }
}

/**
 * @brief Adds a static file to the list with its full path and content type.
 * 
 * @param fileName The name of the file.
 * @param FullPath The full path to the file.
 * @param ContentType The content type of the file.
 */
void serve_static::Static::AddFileFullPath(std::string fileName, std::string FullPath, Enums::CONTENT_TYPE ContentType){
    serve_static::StaticFile nFile;
    nFile.FileName = fileName;
    nFile.ContentType = ContentType;
    nFile.FullPath = FullPath;
    this->static_files.push_back(nFile);
}

/**
 * @brief Adds a static file to the list of static files to be served.
 * 
 * @param FileName The name of the file to be added.
 * @param ContentType The content type of the file to be added.
 */
void serve_static::Static::AddFile(std::string FileName, Enums::CONTENT_TYPE ContentType){
    serve_static::StaticFile nFile;
    nFile.ContentType = ContentType;
    nFile.FileName = FileName;
    std::cout << "nFile.FileName " << nFile.FileName << std::endl;
    this->static_files.push_back(nFile);
}