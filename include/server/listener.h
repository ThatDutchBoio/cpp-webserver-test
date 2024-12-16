#pragma once
#include <string>
#include "./request.h"
#include "./response.h"

typedef void (*callback_function)(Request, Response);

/**
 * @struct Listener
 * @brief Represents a listener that handles callbacks for a specific path.
 * 
 * This structure is used to define a listener that associates a callback function
 * with a specific path. When a request is made to the specified path, the callback
 * function will be invoked.
 * 
 * @var Listener::Callback
 * The callback function that will be invoked when a request is made to the specified path.
 * 
 * @var Listener::Path
 * The path for which the callback function is registered.
 */
struct Listener {
    callback_function Callback;
    std::string Path;
};