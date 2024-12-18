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

        this->AddFile(entry.path().filename(),Enums::TEXT_PLAIN);
    
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

// Router::Router serve_static::Serve_Static(Static s){
//     Router::Router nRouter;
//     for (StaticFile file : s.static_files) {
//         // nRouter.GetStatic(file.FileName, [&](RequestHelper::Request req, ResponseHelper::Response res){
//         //     std::cout << sFile.ContentType << std::endl;
//         //     std::cout << "Static Path: /" << sFile.FileName << " Called!" << std::endl;
//         //     std::cout << "Getting file: " << s.folder_path + "/" + file.FileName << std::endl;
//         //     std::string FileContents;
//         //     if (sFile.FullPath == ""){
//         //         FileContents = file_parser::FileParser::GetFileContents(s.folder_path + "/" + sFile.FileName);
//         //     }else {
//         //         FileContents = file_parser::FileParser::GetFileContents(sFile.FullPath);
//         //     }
            
//         //     std::cout << "FileContents: " << FileContents << std::endl;
//         //     res.SetContentType(file.ContentType);
//         //     res.SetBody(FileContents);
//         //     res.SetStatus(Enums::HTTP_OK);
//         //     res.Send();
//         // }, file);
//         nRouter.GetStatic(file.FileName, [&](RequestHelper::Request req, ResponseHelper::Response res){

//         });
//     }
//     return nRouter;

// }
