# Project Documentation

## Table of Contents
- [Introduction](#introduction)
- [Project Structure](#project-structure)
    - [Classes and Functions](#classes-and-functions)
        - [Server](#server)
        - [Listener](#listener)
        - [Request](#request)
        - [Response](#response)
        - [Router](#router)
        - [FileParser](#fileparser)
        - [StringUtils](#stringutils)
        - [Constants](#constants)
- [Usage](#usage)
- [Building and Running](#building-and-running)

## Introduction
This project is a simple C++ web server that handles HTTP requests and responses. It supports basic routing and can serve static HTML files.

## Project Structure

### Classes and Functions

#### Server
Defined in `server.h`

**Public Methods:**
- `Server(sockaddr_in serverAddr)`: Constructor to initialize the server with a given address.
- `~Server()`: Destructor to clean up resources.
- `void Start()`: Starts the server and begins listening for connections.
- `void Stop()`: Stops the server and closes all connections.
- `void HandleSignal(int signal)`: Handles signals for graceful shutdown.
- `void HandleClient(int client_sock)`: Handles client connections.
- `void Get(const std::string& Path, callback_function func)`: Registers a GET route with a callback function.
- `void ProcessRequest(sockaddr_in Source, const std::string& buffer, int client_sock)`: Processes incoming requests.
- `int GetSocketId()`: Returns the server socket ID.

**Private Members:**
- `int server_sock`: Server socket ID.
- `bool running`: Server running state.
- `sockaddr_in serverAddr`: Server address.
- `std::vector<Listener> listeners`: List of registered listeners.

#### Listener
Defined in `listener.h`

**Members:**
- `callback_function Callback`: Function pointer for the callback.
- `std::string Path`: Path for the listener.

#### Request
Defined in `request.h`

**Members:**
- `int RequestMethod`: HTTP request method.
- `std::string Path`: Request path.
- `sockaddr_in Source_Address`: Source address of the request.
- `std::string body`: Request body.

**Namespaces:**
- `RequestHelper`: Contains helper functions for parsing requests.

**Functions:**
- `RequestHelper::requestInfo ParseRequest(const std::string& buffer)`: Parses the request buffer into a structured format.
- `RequestHelper::requestInfo ParseRequestType(const std::string& buffer)`: Parses the request type from the buffer.

#### Response
Defined in `response.h`

**Public Methods:**
- `Response(int SocketId, int ClientSock)`: Constructor to initialize the response.
- `void SetContentType(Enums::CONTENT_TYPE content_type)`: Sets the content type of the response.
- `void SetStatus(const std::string& status)`: Sets the HTTP status of the response.
- `void SetBody(const std::string& nBody)`: Sets the body of the response.
- `void Send()`: Sends the response to the client.

**Private Members:**
- `std::string GetContentLength()`: Returns the content length as a string.
- `std::string GetContentType()`: Returns the content type as a string.
- `std::string HTTP_Version`: HTTP version.
- `int Content_Length`: Content length.
- `std::string HTTP_Status`: HTTP status.
- `int SocketId`: Server socket ID.
- `std::string body`: Response body.
- `std::string Content_type`: Content type.
- `int ClientSock`: Client socket ID.

#### Router
Defined in `router.h`

**Public Methods:**
- `Router()`: Constructor for the router.

#### FileParser
Defined in `file_parser.h`

**Public Methods:**
- `static std::string GetHTMLPage(const std::string& path)`: Reads an HTML file from the given path and returns its contents as a string.

#### StringUtils
Defined in `string_utils.h`

**Public Methods:**
- `static bool Contains(const std::string& str, const std::string& substr)`: Checks if a string contains a substring.

#### Constants
Defined in `constants.h`

**Members:**
- `char HTTP_GET[3]`: HTTP GET method.
- `char HTTP_POST[4]`: HTTP POST method.

**Enums:**
- `typedef char HTTP_STATUS[8]`: HTTP status type.
- `typedef std::string CONTENT_TYPE`: Content type.
- `int HTTP_G`: HTTP GET enum.
- `int HTTP_P`: HTTP POST enum.
- `int HTTP_PU`: HTTP PUT enum.
- `HTTP_STATUS HTTP_OK`: HTTP 200 OK status.
- `CONTENT_TYPE TEXT_PLAIN`: Plain text content type.
- `CONTENT_TYPE TEXT_HTML`: HTML content type.
- `CONTENT_TYPE TEXT_JSON`: JSON content type.

## Usage
- Define routes using the `Server::Get` method.
- Start the server using the `Server::Start` method.
- Handle client requests and send responses using the `Request` and `Response` classes.

## Building and Running
To build and run the project, follow these steps:
1. Open a terminal and navigate to the project directory.
2. Run the build script:
3. Run the compiled executable:
4. The server will start and listen for incoming connections on the specified port.
