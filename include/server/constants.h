#pragma once
#include <string>

/**
 * @file constants.h
 * @brief This file contains constant definitions and type aliases for HTTP content types and status codes.
 */

namespace Enums {
    /**
     * @typedef CONTENT_TYPE
     * @brief Alias for std::string representing the content type of HTTP responses.
     */

    /**
     * @typedef HTTP_STATUS
     * @brief Alias for a character array of size 8 representing HTTP status codes.
     */

    typedef std::string CONTENT_TYPE;

    /**
     * @var TEXT_PLAIN
     * @brief Constant for the "text/plain" content type.
     */

    /**
     * @var TEXT_HTML
     * @brief Constant for the "text/html" content type.
     */

    /**
     * @var TEXT_JSON
     * @brief Constant for the "application/json" content type.
     */

    /**
     * @var HTTP_OK
     * @brief Constant for the "200 OK" HTTP status code.
     */
    typedef char HTTP_STATUS[14];

    const CONTENT_TYPE TEXT_PLAIN = "text/plain";
    const CONTENT_TYPE TEXT_HTML = "text/html";
    const CONTENT_TYPE TEXT_JSON = "application/json";

    const HTTP_STATUS HTTP_OK = "200 OK";
    const HTTP_STATUS HTTP_NOTFOUND = "404 Not Found";

    typedef int HTTP_METHOD;

    const HTTP_METHOD HTTP_GET = 0;
    const HTTP_METHOD HTTP_POST = 1;
    const HTTP_METHOD HTTP_PUT = 2;
}