#include "../../include/server/response.h"
#include <unistd.h>
#include <sstream>
#include <sys/socket.h>

Response::Response(int SocketId, int ClientSock) : SocketId(SocketId), ClientSock(ClientSock) {}

void Response::SetContentType(Enums::CONTENT_TYPE content_type) {
    this->Content_type = content_type;
}

void Response::SetStatus(const std::string& status) {
    this->HTTP_Status = status;
}

void Response::SetBody(const std::string& nBody) {
    this->body = nBody;
    this->Content_Length = nBody.size();
}

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

std::string Response::GetContentLength() {
    return std::to_string(Content_Length);
}

std::string Response::GetContentType() {
    return Content_type;
}