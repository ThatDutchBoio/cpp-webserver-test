#include <vector>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include "./Request.h"
#include "./Response.h"
#include <iostream>
#include "./StringUtils.h"
// #include "./Constants.h"

typedef void (*callback_function)(void);

struct Listener{
    callback_function Callback;
    char* Path;
};

class Server{
    public:
        Server(sockaddr_in serverAddr);
        ~Server();
        void Start();
        void Stop();
        void HandleSignal(int signal);
        void HandleClient(int client_sock);
        void Get(char Path[256], callback_function func);
        void ProcessRequest(sockaddr_in Source, char buffer[1024], int client_sock);
        int GetSocketId();
    private:
        int server_sock = -1;
        bool running = true;
        sockaddr_in serverAddr;
        std::vector<Listener> listeners;
};

void Server::Get(char Path[256], callback_function func){
    Listener nListener;
    nListener.Callback = func;
    nListener.Path = Path;
    this->listeners.push_back(nListener);
}


Server::Server(sockaddr_in serverAddr){
    this->serverAddr = serverAddr;
}

Server::~Server(){
    if (server_sock >= 0) {
        close(server_sock);
    }
}

void Server::Stop(){
    std::cout << "Terminating server" << std::endl;
    for (int i = 0; i <= 3; i++) {
        close(i);
    }
    this->running = false;
    if (server_sock >= 0) {
        close(server_sock);
    }
}

int Server::GetSocketId(){
    return this->server_sock;
}

void Server::Start(){
    int newSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (newSocket < 0) {
        perror("Socket creation failed");
        return;
    }

    server_sock = newSocket;
    // std::cout << newSocket;
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
    while (this->running){
        struct sockaddr_in CLIENT_ADDRESS;
        socklen_t clientSize = sizeof(CLIENT_ADDRESS);
        int client_sock = accept(newSocket, (struct sockaddr*) &CLIENT_ADDRESS, &clientSize);

        if (client_sock < 0) {
            perror("Accept failed");
            continue;
        }

        char buffer[1024];
        ssize_t bytes_received = recv(client_sock, buffer, sizeof(buffer),0);
        this->ProcessRequest(CLIENT_ADDRESS, buffer, client_sock);
    }
    
}

void Server::ProcessRequest(sockaddr_in CLIENT_ADDRESS, char buffer[1024], int client_sock){
    RequestHelper::requestInfo Parsed = RequestHelper::ParseRequest(buffer);
    RequestHelper::requestInfo requestInfo = RequestHelper::ParseRequestType(Parsed[0]);

    std::cout << "Request path: " << requestInfo[1].data() << std::endl;
    std::cout << "Request type: " << requestInfo[0].data() << std::endl;
    // std::cout << buffer << std::endl;
    
    char toCheck[] = "/terminate";
    if (StringUtils::Contains(requestInfo[1].data(), toCheck)) {
        this->Stop();
    }
    Response r(this->server_sock, client_sock);
    r.SetStatus(Enums::HTTP_OK);
    char body[] = "testing123";
    r.SetBody(body);
    r.Send();


}