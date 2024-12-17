#pragma once
#include "listener.h"
#include <vector>

namespace Router{
    class Router {
    public:
        Router();
        std::vector<ListenerHelper::Listener> Listeners;
        void Get(const std::string& Path, callback_function func);
    };

}
