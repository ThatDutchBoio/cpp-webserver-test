#include "../../include/server/server.h"
#include "../../include/server/request.h"
#include "../../include/server/router.h"
#include "../../include/server/constants.h"
using namespace ListenerHelper;
using namespace RequestHelper;
using namespace ResponseHelper;
using namespace Router;
#include <chrono>

/**
 * @brief Registers a callback function for a specific HTTP GET request path.
 * 
 * @param Path The URL path to listen for GET requests.
 * @param func The callback function to be invoked when a GET request is received for the specified path.
 */
void Server::Get(const std::string& Path, callback_function func) {
    ListenerHelper::Listener nListener;
    nListener.Callback = func;
    nListener.Path = Path;
    nListener.Method = Enums::HTTP_GET;
    this->listeners.push_back(nListener);
}

/**
 * @brief Constructs a new Server object with the specified server address.
 * 
 * @param serverAddr The sockaddr_in structure containing the server address.
 */
Server::Server(sockaddr_in serverAddr) {
    this->serverAddr = serverAddr;
}

/**
 * @brief Destructor for the Server class.
 *
 * This destructor closes the server socket if it is open (i.e., if the socket
 * file descriptor is greater than or equal to 0). This ensures that any
 * resources associated with the server socket are properly released when
 * the Server object is destroyed.
 */
Server::~Server() {
    if (server_sock >= 0) {
        close(server_sock);
    }
}

/**
 * @brief Stops the server and closes all open file descriptors.
 * 
 * This function terminates the server by setting the running flag to false
 * and closing the server socket if it is open. It also closes the first four
 * file descriptors (0, 1, 2, 3) which are typically standard input, output,
 * error, and an additional descriptor.
 */
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

/**
 * @brief Starts the server to listen for incoming connections.
 * 
 * This function creates a socket, binds it to the specified address and port,
 * and starts listening for incoming connections. It enters a loop where it
 * accepts client connections and processes their requests.
 * 
 * @details
 * - Creates a socket using the `socket` function.
 * - Binds the socket to the server address using the `bind` function.
 * - Listens for incoming connections using the `listen` function.
 * - Enters a loop to accept and handle client connections.
 * - For each client connection:
 *   - Accepts the connection using the `accept` function.
 *   - Receives data from the client using the `recv` function.
 *   - Processes the client's request by calling `ProcessRequest`.
 * 
 * @note If any of the socket operations (creation, binding, listening, accepting, receiving) fail,
 *       an error message is printed using `perror`, and the server stops or continues based on the context.
 * 
 * @warning This function runs in an infinite loop until `this->running` is set to false.
 * 
 * @see Server::Stop
 * @see Server::ProcessRequest
 */
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

/**
 * @brief Processes an incoming client request.
 * 
 * This function parses the incoming request, logs the request path and type,
 * and checks if the request path matches any registered listeners. If a match
 * is found, the corresponding callback is invoked. Additionally, if the request
 * path matches the termination path ("/terminate"), the server is stopped.
 * 
 * @param CLIENT_ADDRESS The address of the client making the request.
 * @param buffer The raw request data received from the client.
 * @param client_sock The socket file descriptor for the client connection.
 */
void Server::ProcessRequest(sockaddr_in CLIENT_ADDRESS, const std::string& buffer, int client_sock) {
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;
    auto t1 = high_resolution_clock::now();
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
        std::cout << "l.path: " << l.Path << std::endl << "request Path: " << requestInfo[1][0] << std::endl;
        if (l.Path == requestInfo[1][0]) {
            std::cout << "in request, is_static?: " << l.is_static << std::endl;
           if (l.is_static == true) {
                std::cout << "Calling static callback" << std::endl;
                bool isThing = l.CallbackStatic == nullptr;
                std::cout << "is callback nil? " << std::boolalpha << isThing  << std::endl;
                if (!isThing) {
                     l.CallbackStatic(Req, Res, l.file);
                }else {
                    Res.SetBody("Couldn't fetch " + l.Path);
                    Res.SetStatus(Enums::HTTP_NOTFOUND);
                    Res.SetContentType(Enums::TEXT_PLAIN);
                    Res.Send();
                }
           }else {
            std::cout << "Calling normal callback" << std::endl;
                l.Callback(Req, Res);
           }
        }
    }
    auto t2 = high_resolution_clock::now();

    /* Getting number of milliseconds as a double. */
    duration<double, std::milli> ms_double = t2 - t1;
    std::cout << "Time Until request processed: " << ms_double.count() << "ms" << std::endl;
}


/**
 * @brief Registers the routes from the given Router to the Server with the specified base path.
 * 
 * This function iterates through all the listeners in the provided Router, 
 * prepends the specified base path to each listener's path, and adds the 
 * modified listeners to the server's list of listeners. After adding the 
 * listeners to the server, it clears the listeners from the Router.
 * 
 * @param Path The base path to be prepended to each listener's path.
 * @param R The Router containing the listeners to be registered.
 */
void Server::Use(std::string Path, Router::Router R){
    for (Listener l : R.Listeners) {
        Listener nListener;
        // nListener.Callback = l.Callback;
        // nListener.Method = l.Method;
        // nListener.Path = Path + l.Path;
        // nListener.is_static = l.is_static;
        // nListener.file = l.file;
        // nListener
        nListener = l;
        std::cout << "is_static?: " << nListener.is_static << std::endl;;
        std::cout << l.Path << std::endl;
        this->listeners.push_back(nListener);
    }
    R.Listeners.clear();
}