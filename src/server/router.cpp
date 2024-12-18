#include "../../include/server/router.h"
#include "../../include/server/listener.h"
#include "../../include/server/static.h"
#include "../../include/server/file_parser.h"
#include <iostream>

Router::Router::Router() {}

void Router::Router::Get(const std::string& Path, ListenerHelper::callback_function func) {
    ListenerHelper::Listener nListener;
    nListener.Callback = func;
    nListener.Path = Path;
    nListener.Method = Enums::HTTP_GET;
    nListener.is_static = false;
    this->Listeners.push_back(nListener);
}

void Router::Router::GetStatic(const std::string& Path, ListenerHelper::callback_function_static func, serve_static::StaticFile file) {
    ListenerHelper::Listener nListener;
    nListener.CallbackStatic = func;
    nListener.Path = Path;
    nListener.Method = Enums::HTTP_GET;
    nListener.file = file;
    nListener.is_static = true;
    this->Listeners.push_back(nListener);
}


Router::Router Router::Serve_Static(serve_static::Static s){
    Router nRouter;

    for (serve_static::StaticFile file : s.static_files){
        std::cout << "s.url_path: " << s.url_path << std::endl << "file.FileName: " << file.FileName << std::endl;
        nRouter.GetStatic(s.url_path + file.FileName, [](RequestHelper::Request req, ResponseHelper::Response res, serve_static::StaticFile file){
            std::string fileContents = file_parser::FileParser::GetFileContents(file.FullPath);

            res.SetBody(fileContents);
            res.SetStatus(Enums::HTTP_OK);
            res.SetContentType(file.ContentType);
            res.Send();
        },file);
    }

    return nRouter;
}