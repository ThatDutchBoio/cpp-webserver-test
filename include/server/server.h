#pragma once
#include <vector>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include "request.h"
#include "response.h"
#include "string_utils.h"
#include "listener.h"

class Server {
public:
    Server(sockaddr_in serverAddr);
    ~Server();
    void Start();
    void Stop();
    void HandleSignal(int signal);
    void HandleClient(int client_sock);
    void Get(const std::string& Path, callback_function func);
    void ProcessRequest(sockaddr_in Source, const std::string& buffer, int client_sock);
    int GetSocketId();
private:
    int server_sock = -1;
    bool running = true;
    sockaddr_in serverAddr;
    std::vector<Listener> listeners;
};