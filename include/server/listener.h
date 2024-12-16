#pragma once
#include <string>
#include "./request.h"
#include "./response.h"

typedef void (*callback_function)(Request, Response);

struct Listener {
    callback_function Callback;
    std::string Path;
};