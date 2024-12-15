#include <iostream>
#include <cstring>
#include "Constants.h"
#include <string>

int roundUpToNearestMultipleOf2(int num) {
    // If the number is already a multiple of 2, return it as is.
    if (num % 2 == 0) {
        return num;
    }

    // Otherwise, round up to the next multiple of 2
    return (num / 2 + 1) * 2;
}

void intToCharArray(int num, char* buffer) {
    int index = 0;
    if (num == 0) {
        buffer[index++] = '0';
    } else {
        if (num < 0) {
            buffer[index++] = '-';
            num = -num;
        }
        // Convert digits to characters
        int digits[10];
        int digitCount = 0;
        while (num > 0) {
            digits[digitCount++] = num % 10;
            num /= 10;
        }
        for (int i = digitCount - 1; i >= 0; --i) {
            buffer[index++] = '0' + digits[i];
        }
    }
    buffer[index] = '\0'; // Null-terminate
}


class Response{
    public:
        Response(int SocketId, int ClientSock);
        void SetBody(char* body);
        void SetStatus(Enums::HTTP_STATUS status);
        void Send();
        
    private:
        std::string GetContentLength();
        std::string GetContentType();
        char HTTP_Version[10]; // "HTTP/1.1" + null terminator
        int Content_Length = 35;
        char HTTP_Status[50]; // Assuming max status length
        int SocketId;
        char body[2048]; // Assuming max body length
        std::string Content_type = "text/plain";
        int ClientSock;
};

std::string Response::GetContentLength(){
    std::string strOne = "Content-Length: ";
    std::string res = strOne + std::to_string(this->Content_Length);
    return res;
}

std::string Response::GetContentType(){
    std::string res = "Content-Type: " + this->Content_type;
    return res;
}

Response::Response(int SocketId, int ClientSock){
    this->SocketId = SocketId;
    this->ClientSock = ClientSock;
    char version[] = "HTTP/1.1";
    strcpy(HTTP_Version, version);
    this->Content_Length += strlen(this->HTTP_Version);
}

void Response::SetStatus(Enums::HTTP_STATUS status){
    strcpy(HTTP_Status, status);
    this->Content_Length += strlen(this->HTTP_Status);
}

void Response::SetBody(char* nBody){
    strcpy(body, nBody);
    this->Content_Length += strlen(body);
}

/*
    "HTTP_VERSION HTTP_STATUS\r\n

*/
    //         "HTTP/1.1 200 OK\r\n"
    //         "Content-Type: text/plain\r\n"
    //         "Content-Length: 12\r\n"
    //         "\r\n"
    //         "Testing!";
void Response::Send() {
    // Calculate the content length correctly
    this->Content_Length = strlen(this->HTTP_Version) + strlen(this->HTTP_Status) + 12 + // Headers before body
                           this->GetContentType().length() + this->GetContentLength().length() + strlen(this->body) + 2; // Content-Type, Content-Length, Body, CRLFs

    // Round content length to nearest multiple of 2
    this->Content_Length = roundUpToNearestMultipleOf2(this->Content_Length);

    std::cout << "Content Length: " << this->GetContentLength() << std::endl;

    // Dynamically allocate the buffer with correct size
    char* buffer = new char[this->Content_Length];
    int curIndex = 0;

    // Add HTTP Version
    for (int i = 0; i < strlen(this->HTTP_Version); i++) {
        buffer[curIndex++] = this->HTTP_Version[i];
    }

    buffer[curIndex++] = ' ';
    // Add HTTP Status
    for (int i = 0; i < strlen(this->HTTP_Status); i++) {
        buffer[curIndex++] = this->HTTP_Status[i];
    }

    buffer[curIndex++] = '\r';
    buffer[curIndex++] = '\n';

    // Add Content-Type
    std::string cType = this->GetContentType();
    int cTypeLength = cType.length();
    if (curIndex + cTypeLength <= this->Content_Length) {
        for (int i = 0; i < cTypeLength; i++) {
            buffer[curIndex++] = cType[i];
        }
    } else {
        std::cerr << "Buffer overflow detected when adding Content-Type" << std::endl;
        delete[] buffer;
        return;
    }

    buffer[curIndex++] = '\r';
    buffer[curIndex++] = '\n';

    // Add Content-Length
    std::string cLength = this->GetContentLength();
    for (int i = 0; i < cLength.length(); i++) {
        buffer[curIndex++] = cLength[i];
    }

    buffer[curIndex++] = '\r';
    buffer[curIndex++] = '\n';
    buffer[curIndex++] = '\r';
    buffer[curIndex++] = '\n';

    // Add body content
    for (int i = 0; i < strlen(this->body); i++) {
        if (curIndex >= this->Content_Length) {
            std::cerr << "Buffer overflow detected when adding body" << std::endl;
            delete[] buffer;
            return;
        }
        buffer[curIndex++] = this->body[i];
    }

    // Send data in chunks
    ssize_t bytes_sent = 0, total = this->Content_Length;
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
    // shutdown(this->ClientSock, SHUT_RDWR);
    // close(this->ClientSock);
    delete[] buffer;
}

