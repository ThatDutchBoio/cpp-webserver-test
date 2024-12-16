#pragma once
#include <string>
#include "constants.h"

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