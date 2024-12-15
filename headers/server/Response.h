#include <string>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include "./Constants.h"

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
    int Content_Length = 35;
    std::string HTTP_Status;
    int SocketId;
    std::string body;
    std::string Content_type = "text/html";
    int ClientSock;
};

void Response::SetContentType(Enums::CONTENT_TYPE content_type) {
    this->Content_type = content_type;
}

std::string Response::GetContentLength() {
    return "Content-Length: " + std::to_string(this->Content_Length);
}

std::string Response::GetContentType() {
    return "Content-Type: " + this->Content_type;
}

Response::Response(int SocketId, int ClientSock) {
    this->SocketId = SocketId;
    this->ClientSock = ClientSock;
    this->Content_Length += this->HTTP_Version.length();
}

void Response::SetStatus(const std::string& status) {
    this->HTTP_Status = status;
    this->Content_Length += this->HTTP_Status.length();
}

void Response::SetBody(const std::string& nBody) {
    this->body = nBody;
    this->Content_Length += this->body.length();
}

void Response::Send() {
    // Construct the response string
    std::string response;

    // Add HTTP Version and Status
    response += this->HTTP_Version;
    response += " ";
    response += this->HTTP_Status;
    response += "\r\n";

    // Add Content-Type
    response += this->GetContentType();
    response += "\r\n";

    // Add Content-Length
    response += this->GetContentLength();
    response += "\r\n\r\n";

    // Add body content
    response += this->body;

    // Calculate the content length correctly
    this->Content_Length = response.length();

    std::cout << "Content Length: " << this->GetContentLength() << std::endl;

    // Send data in chunks
    ssize_t bytes_sent = 0, total = this->Content_Length;
    const char* buffer = response.c_str();
    while (bytes_sent < total) {
        ssize_t bytes = send(this->ClientSock, buffer + bytes_sent, total - bytes_sent, 0);
        if (bytes < 0) {
            perror("Error sending response");
            break;
        } else {
            std::cout << "Sent " << bytes << " bytes" << std::endl;
        }
        bytes_sent += bytes;
    }

    // Cleanup and shutdown
    shutdown(this->ClientSock, SHUT_RDWR);
    close(this->ClientSock);
}