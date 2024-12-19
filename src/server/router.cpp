#include "../../include/server/router.h"
#include "../../include/server/listener.h"
#include "../../include/server/static.h"
#include "../../include/server/file_parser.h"
#include <iostream>

Router::Router::Router() {}

/**
 * @brief Registers a GET route with the specified path and callback function.
 * 
 * @param Path The URL path for the GET route.
 * @param func The callback function to be executed when the route is accessed.
 */
void Router::Router::Get(const std::string& Path, ListenerHelper::callback_function func) {
    ListenerHelper::Listener nListener;
    nListener.Callback = func;
    nListener.Path = Path;
    nListener.Method = Enums::HTTP_GET;
    nListener.is_static = false;
    this->Listeners.push_back(nListener);
}

/**
 * @brief Registers a POST route with the specified path and callback function.
 * 
 * @param Path The URL path for the GET route.
 * @param func The callback function to be executed when the route is accessed.
 */

void Router::Router::Post(const std::string& Path, ListenerHelper::callback_function func) {
    ListenerHelper::Listener nListener;
    nListener.Callback = func;
    nListener.Path = Path;
    nListener.Method = Enums::HTTP_POST;
    nListener.is_static = false;
    this->Listeners.push_back(nListener);
}


/**
 * @brief Registers a static file handler for HTTP GET requests.
 *
 * This function registers a new listener that serves static files when an HTTP GET request
 * is made to the specified path.
 *
 * @param Path The URL path to associate with the static file handler.
 * @param func The callback function to be called when the path is requested.
 * @param file The static file to be served when the path is requested.
 */
void Router::Router::GetStatic(const std::string& Path, ListenerHelper::callback_function_static func, serve_static::StaticFile file) {
    ListenerHelper::Listener nListener;
    nListener.CallbackStatic = func;
    nListener.Path = Path;
    nListener.Method = Enums::HTTP_GET;
    nListener.file = file;
    nListener.is_static = true;
    this->Listeners.push_back(nListener);
}


/**
 * @brief Serves static files by setting up routes for each static file.
 * 
 * This function takes a `serve_static::Static` object which contains a list of static files
 * and their associated URL paths. It sets up routes for each static file, so that when a request
 * is made to the URL path, the corresponding static file is served.
 * 
 * @param s A `serve_static::Static` object containing the URL path and a list of static files.
 * @return A new `Router` object with routes set up for serving the static files.
 */
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