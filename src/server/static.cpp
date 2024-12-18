#include "../../include/server/static.h"
#include "../../include/server/file_parser.h"
#include "../../include/server/request.h"
#include "../../include/server/response.h"
// using namespace serve_static;
#include <filesystem>
#include <iostream>
#include <vector>
namespace fs = std::filesystem;


serve_static::Static::Static(std::string url_path, std::string folder_path){
    this->url_path = url_path;
    this->folder_path = folder_path;
    for (const auto & entry : fs::directory_iterator(folder_path)){
        std::cout << entry.path() << std::endl;
        std::cout << entry.path().filename() << std::endl;
        this->AddFileFullPath(entry.path().filename(), entry.path(), Enums::TEXT_PLAIN);    
    }
}

void serve_static::Static::AddFileFullPath(std::string fileName, std::string FullPath, Enums::CONTENT_TYPE ContentType){
    serve_static::StaticFile nFile;
    nFile.FileName = fileName;
    nFile.ContentType = ContentType;
    nFile.FullPath = FullPath;
    this->static_files.push_back(nFile);
}

void serve_static::Static::AddFile(std::string FileName, Enums::CONTENT_TYPE ContentType){
    serve_static::StaticFile nFile;
    nFile.ContentType = ContentType;
    nFile.FileName = FileName;
    std::cout << "nFile.FileName " << nFile.FileName << std::endl;
    this->static_files.push_back(nFile);
}