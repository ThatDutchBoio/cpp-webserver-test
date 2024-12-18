// #pragma once
#ifndef LISTENER_H
#define LISTENER_H
#pragma message("Including listener.h")
#include <functional>
#include <string>
#include "request.h"
#include "response.h"
// #include "static.h"
#include "constants.h"



namespace ListenerHelper {
    
    typedef void (*callback_function)(RequestHelper::Request, ResponseHelper::Response);
    typedef std::function<void(RequestHelper::Request, ResponseHelper::Response)> callback_function_static;
    struct Listener {
        bool is_static;
        callback_function Callback;
        callback_function_static CallbackStatic;
        std::string Path;
        Enums::HTTP_METHOD Method;
        
    };
}

#endif // LISTENER_H
