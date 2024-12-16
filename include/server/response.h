#pragma once
#include <string>
#include "constants.h"

/**
 * @class Response
 * @brief Handles the HTTP response for the web server.
 * 
 * This class is responsible for constructing and sending HTTP responses
 * to the client. It includes methods to set the content type, status,
 * and body of the response, as well as sending the response over the socket.
 */
 
/**
 * @brief Constructs a new Response object.
 * 
 * @param SocketId The socket identifier for the server.
 * @param ClientSock The socket identifier for the client.
 */
 
/**
 * @brief Sets the content type of the response.
 * 
 * @param content_type The content type to be set (e.g., text/html, application/json).
 */
 
/**
 * @brief Sets the HTTP status of the response.
 * 
 * @param status The HTTP status to be set (e.g., 200 OK, 404 Not Found).
 */
 
/**
 * @brief Sets the body of the response.
 * 
 * @param nBody The body content to be set.
 */
 
/**
 * @brief Sends the constructed HTTP response to the client.
 */
 
/**
 * @brief Gets the content length of the response body.
 * 
 * @return The content length as a string.
 */
 
/**
 * @brief Gets the content type of the response.
 * 
 * @return The content type as a string.
 */
class Response {
public:
    Response(int SocketId, int ClientSock);
    void SetContentType(Enums::CONTENT_TYPE content_type);
    void SetStatus(const std::string& status);
    void SetBody(const std::string& nBody);
    void Send();
private:
    std::string GetContentLength();
    std::string GetContentType();
    std::string HTTP_Version = "HTTP/1.1";
    int Content_Length = 0;
    std::string HTTP_Status;
    int SocketId;
    std::string body;
    std::string Content_type;
    int ClientSock;
};