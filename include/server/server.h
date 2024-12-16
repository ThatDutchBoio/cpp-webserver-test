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

/**
 * @class Server
 * @brief A class to represent a web server.
 * 
 * This class provides functionalities to start, stop, and handle client connections
 * for a web server. It also allows registering callback functions for specific paths.
 */
 
/**
 * @brief Constructs a new Server object.
 * 
 * @param serverAddr The address of the server.
 */
 
/**
 * @brief Destroys the Server object.
 */
 
/**
 * @brief Starts the server.
 */
 
/**
 * @brief Stops the server.
 */
 
/**
 * @brief Handles signals sent to the server.
 * 
 * @param signal The signal to handle.
 */
 
/**
 * @brief Handles a client connection.
 * 
 * @param client_sock The socket of the client.
 */
 
/**
 * @brief Registers a callback function for a specific path.
 * 
 * @param Path The path to register the callback for.
 * @param func The callback function to register.
 */
 
/**
 * @brief Processes a request from a client.
 * 
 * @param Source The source address of the request.
 * @param buffer The request data.
 * @param client_sock The socket of the client.
 */
 
/**
 * @brief Gets the socket ID of the server.
 * 
 * @return The socket ID.
 */
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