#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <csignal>
#include <vector>
#include "./headers/server/Server.h"
#include "./headers/server/IPv4.h"

// int server_sock = -1;
// bool running = true;
sockaddr_in ServerAddr = createServerAddress(8080, "87.106.130.229");
Server App(ServerAddr);

void handle_signal(int signal)
{
    std::cout << "Handling signal!!" << std::endl;
    App.Stop();
}

int main()
{

    // signal(SIGTERM, handle_signal);
    signal(SIGABRT, handle_signal);

    int Server_Socket = App.GetSocketId();

    App.Start();
    // std::cout << "Starting server..." << std::endl;
    // int newSocket = socket(AF_INET, SOCK_STREAM, 0);
    // if (newSocket < 0) {
    //     perror("Socket creation failed");
    //     return 1;
    // }
    // server_sock = newSocket;

    // struct sockaddr_in serverAddr;
    // serverAddr.sin_family = AF_INET;
    // serverAddr.sin_port = htons(8080);
    // serverAddr.sin_addr.s_addr = INADDR_ANY; // Bind to all available interfaces

    // if (bind(newSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
    //     perror("Bind failed");
    //     close(newSocket);
    //     return 1;
    // }

    // if (listen(newSocket, 10) < 0) {
    //     perror("Listen failed");
    //     close(newSocket);
    //     return 1;
    // } else {
    //     std::cout << "Server is listening on port 8080..." << std::endl;
    // }

    // while (running) {
    //     struct sockaddr_in CLIENT_ADDRESS;
    //     socklen_t clientSize = sizeof(CLIENT_ADDRESS);
    //     int client_sock = accept(newSocket, (struct sockaddr *)&CLIENT_ADDRESS, &clientSize);

    //     if (client_sock < 0) {
    //         perror("Accept failed");
    //         continue;
    //     }

    //     char buffer[1024];
    //     ssize_t bytes_received = recv(client_sock, buffer, sizeof(buffer), 0);

    //     std::vector<std::vector<char>> request = RequestHelper::ParseRequest(buffer);
    //     // printing request type
    //     for (int i = 0; i < request[0].size(); i++){
    //         std::cout << request[0][i];
    //     }
    //     std::cout << std::endl;
    //     std::cout << "Connection accepted from " << inet_ntoa(CLIENT_ADDRESS.sin_addr) << ":" << ntohs(CLIENT_ADDRESS.sin_port) << std::endl;
    //     RequestHelper::requestInfo requestInfo = RequestHelper::ParseRequestType(request[0]);
    //     std::cout << "Request path: " << requestInfo[1].data() << std::endl;
    //     std::cout << "Request type: " << requestInfo[0].data() << std::endl;
    //     bool isGet = StringUtils::Contains(requestInfo[0].data(), Constants::HTTP_GET);
    //     std::cout << "is GET?: " << isGet << std::endl;
    //     char response[] =
    //         "HTTP/1.1 200 OK\r\n"
    //         "Content-Type: text/plain\r\n"
    //         "Content-Length: 12\r\n"
    //         "\r\n"
    //         "Testing!";
    // https://open.spotify.com/track/3DVjSnt1HId4Qb8oL5Mjs8?si=6992d77e438d4b03
    //     ssize_t bytes_sent = 0, total = sizeof(response) - 1;
    //     while (bytes_sent < total) {
    //         ssize_t bytes = send(client_sock, response + bytes_sent, total - bytes_sent, 0);
    //         if (bytes < 0) {
    //             perror("Error sending response");
    //             break;
    //         }else {
    //             std::cout << "Sent " << bytes << " bytes" << std::endl;
    //         }
    //         bytes_sent += bytes;
    //     }

    //     shutdown(client_sock, SHUT_RDWR);
    //     close(client_sock);
    // }

    // close(newSocket);
}
