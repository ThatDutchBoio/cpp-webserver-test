#pragma once
#pragma message("including static.h")
#include <string>
#include "constants.h"
// #include "router.h"

namespace serve_static {
    struct StaticFile {
        std::string FileName;
        Enums::CONTENT_TYPE ContentType;
        std::string FullPath;
        std::string SubPath;

        // StaticFile(std::string fileName, Enums::CONTENT_TYPE contentType)
        //     : FileName(fileName), ContentType(contentType) {}
    };

    class Static {
    public:
        std::string url_path;
        std::string folder_path;
        std::vector<StaticFile> static_files;

        Static(std::string url_path, std::string folder_path)
            : url_path(url_path), folder_path(folder_path) {}

        void AddFile(std::string FileName, Enums::CONTENT_TYPE ContentType);
        void AddFileFullPath(std::string fileName, std::string FullPath, Enums::CONTENT_TYPE ContentType);
    };


}