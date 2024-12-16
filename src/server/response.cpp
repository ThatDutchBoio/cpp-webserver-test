#include "../../include/server/response.h"
#include <unistd.h>
#include <sstream>
#include <sys/socket.h>

/**
 * @brief Constructs a new Response object.
 * 
 * @param SocketId The ID of the server socket.
 * @param ClientSock The socket ID of the client connection.
 */
Response::Response(int SocketId, int ClientSock) : SocketId(SocketId), ClientSock(ClientSock) {}

/**
 * @brief Sets the content type of the response.
 * 
 * @param content_type The content type to be set for the response.
 */
void Response::SetContentType(Enums::CONTENT_TYPE content_type) {
    this->Content_type = content_type;
}

/**
 * @brief Sets the HTTP status for the response.
 * 
 * @param status A string representing the HTTP status to be set.
 */
void Response::SetStatus(const std::string& status) {
    this->HTTP_Status = status;
}

/**
 * @brief Sets the body of the response and updates the Content-Length header.
 * 
 * @param nBody The new body content to be set.
 */
void Response::SetBody(const std::string& nBody) {
    this->body = nBody;
    this->Content_Length = nBody.size();
}

/**
 * @brief Sends the HTTP response to the client.
 * 
 * This function constructs the HTTP response by combining the HTTP version,
 * status, headers (Content-Length and Content-Type), and the response body.
 * The constructed response is then sent to the client socket and the socket
 * is closed.
 * 
 * @note This function assumes that the HTTP_Version, HTTP_Status, body, 
 *       ClientSock, GetContentLength(), and GetContentType() are properly 
 *       initialized and valid.
 */
void Response::Send() {
    std::ostringstream response;
    response << HTTP_Version << " " << HTTP_Status << "\r\n";
    response << "Content-Length: " << GetContentLength() << "\r\n";
    response << "Content-Type: " << GetContentType() << "\r\n";
    response << "\r\n";
    response << body;
    std::string response_str = response.str();
    send(ClientSock, response_str.c_str(), response_str.size(), 0);
    close(ClientSock);
}

/**
 * @brief Retrieves the content length of the response as a string.
 * 
 * This function converts the Content_Length member variable to a string
 * and returns it. The Content_Length represents the size of the response
 * body in bytes.
 * 
 * @return std::string The content length of the response as a string.
 */
std::string Response::GetContentLength() {
    return std::to_string(Content_Length);
}

/**
 * @brief Retrieves the content type of the response.
 * 
 * @return std::string The content type of the response.
 */
std::string Response::GetContentType() {
    return Content_type;
}