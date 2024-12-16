#pragma once
#include "listener.h"
#include <vector>

class Router {
public:
    Router();
    std::vector<Listener> Listeners;
    void Get(const std::string& Path, callback_function func);
};

