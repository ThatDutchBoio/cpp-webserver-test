#include "../../include/server/server.h"
#include "../../include/server/request.h"

void Server::Get(const std::string& Path, callback_function func) {
    Listener nListener;
    nListener.Callback = func;
    nListener.Path = Path;
    this->listeners.push_back(nListener);
}

Server::Server(sockaddr_in serverAddr) {
    this->serverAddr = serverAddr;
}

Server::~Server() {
    if (server_sock >= 0) {
        close(server_sock);
    }
}

void Server::Stop() {
    std::cout << "Terminating server" << std::endl;
    for (int i = 0; i <= 3; i++) {
        close(i);
    }
    this->running = false;
    if (server_sock >= 0) {
        close(server_sock);
    }
}

int Server::GetSocketId() {
    return this->server_sock;
}

void Server::Start() {
    int newSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (newSocket < 0) {
        perror("Socket creation failed");
        return;
    }

    server_sock = newSocket;
    struct sockaddr_in Server_Address;
    Server_Address.sin_family = AF_INET;
    Server_Address.sin_port = this->serverAddr.sin_port;
    Server_Address.sin_addr.s_addr = INADDR_ANY;

    if (bind(newSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Bind failed");
        this->Stop();
        return;
    }

    if (listen(newSocket, 10) < 0) {
        perror("Listen failed");
        this->Stop();
        return;
    }
    std::cout << "Listening on port 8080" << std::endl;
    while (this->running) {
        struct sockaddr_in CLIENT_ADDRESS;
        socklen_t clientSize = sizeof(CLIENT_ADDRESS);
        int client_sock = accept(newSocket, (struct sockaddr*)&CLIENT_ADDRESS, &clientSize);
        if (client_sock < 0) {
            perror("Accept failed");
            continue;
        }
        char buffer[1024] = {0}; // Initialize buffer to zero
        ssize_t bytes_received = recv(client_sock, buffer, sizeof(buffer) - 1, 0); // Ensure null-termination
        if (bytes_received < 0) {
            perror("Receive failed");
            close(client_sock);
            continue;
        }
        buffer[bytes_received] = '\0'; // Null-terminate the received data
        std::string request(buffer);
        this->ProcessRequest(CLIENT_ADDRESS, request, client_sock);
    }
}

void Server::ProcessRequest(sockaddr_in CLIENT_ADDRESS, const std::string& buffer, int client_sock) {
    RequestHelper::requestInfo Parsed = RequestHelper::ParseRequest(buffer);
    RequestHelper::requestInfo requestInfo = RequestHelper::ParseRequestType(Parsed[0][0]);

    std::cout << "Request path: " << requestInfo[1][0] << std::endl;
    std::cout << "Request type: " << requestInfo[0][0] << std::endl;
    Request Req;
    Req.Path = requestInfo[1][0];
    Req.Source_Address = CLIENT_ADDRESS;
    Response Res(this->server_sock, client_sock);
    std::string toCheck = "/terminate";
    if (StringUtils::Contains(requestInfo[1][0], toCheck)) {
        this->Stop();
    }
    for (Listener l : this->listeners) {
        if (l.Path == requestInfo[1][0]) {
            l.Callback(Req, Res);
        }
    }
}