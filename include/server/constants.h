#pragma once
#include <string>

namespace Enums {
    typedef std::string CONTENT_TYPE;
    typedef char HTTP_STATUS[8];

    const CONTENT_TYPE TEXT_PLAIN = "text/plain";
    const CONTENT_TYPE TEXT_HTML = "text/html";
    const CONTENT_TYPE TEXT_JSON = "application/json";

    const HTTP_STATUS HTTP_OK = "200 OK";
}