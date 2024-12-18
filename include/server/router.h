#pragma once
#pragma message("Including router.h")
#include "listener.h"
#include "static.h"
#include <vector>

namespace Router{
    class Router {
    public:
        Router();
        std::vector<ListenerHelper::Listener> Listeners;
        void Get(const std::string& Path, ListenerHelper::callback_function func);
        void GetStatic(const std::string& Path, ListenerHelper::callback_function_static func); 
        Router Serve_Static(serve_static::Static);
    };

}
