# Project Documentation

## TBD

- [ ] Support for other request types
- [ ] Support for sending/requesting image files
- [ ] Implement more request headers (Security headers, etc.)

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
```
.gitignore
.vscode/
    settings.json
build/
    server
build.sh
buildTrace.sh
docs/
    docs.md
include/
    server/
        constants.h
        file_parser.h
        ipv4.h
        listener.h
        request.h
        response.h
        router.h
        server.h
        static.h
        string_utils.h
main.cpp
preprocessed_output.cpp
public/
    index.html
    script.js
    style.css
test/
    index.test
README.md
src/
    api/
        testing.cpp
    server/
        file_parser.cpp
        ipv4.cpp
        listener.cpp
        request.cpp
        response.cpp
        router.cpp
        server_lib.cpp
        server.cpp

```

### Classes and Functions

#### Server
Defined in [`include/server/server.h`](../include/server/server.h)

**Public Methods:**
- [`Server(sockaddr_in serverAddr)`](../include/server/server.h): Constructor to initialize the server with a given address.
- `~Server()`: Destructor to clean up resources.
- [`void Start()`](../include/server/server.h): Starts the server and begins listening for connections.
- [`void Stop()`](../include/server/server.h): Stops the server and closes all connections.
- `void HandleSignal(int signal)`: Handles signals for graceful shutdown.
- `void HandleClient(int client_sock)`: Handles client connections.
- [`void Get(const std::string& Path, callback_function func)`](../include/server/server.h): Registers a GET route with a callback function.
- [`void ProcessRequest(sockaddr_in Source, const std::string& buffer, int client_sock)`](../include/server/server.h): Processes incoming requests.
- [`int GetSocketId()`](../include/server/server.h): Returns the server socket ID.
- [`void Use(std::string Path, Router::Router& R)`](../include/server/server.h): Registers the routes from the given Router to the Server with the specified base path.

**Private Members:**
- `int server_sock`: Server socket ID.
- `bool running`: Server running state.
- `sockaddr_in serverAddr`: Server address.
- `std::vector<ListenerHelper::Listener> listeners`: List of registered listeners.

#### Listener
Defined in [`include/server/listener.h`](../include/server/listener.h)

**Members:**
- `bool is_static`: Indicates if the listener is for static content.
- `ListenerHelper::callback_function Callback`: Function pointer for the callback.
- `ListenerHelper::callback_function_static CallbackStatic`: Function pointer for static content callback.
- `std::string Path`: Path for the listener.
- `Enums::HTTP_METHOD Method`: HTTP method for the listener.
- `serve_static::StaticFile file`: Static file associated with the listener.

#### Request
Defined in [`include/server/request.h`](../include/server/request.h)

**Members:**
- `int RequestMethod`: HTTP request method.
- `std::string Path`: Request path.
- `sockaddr_in Source_Address`: Source address of the request.
- `std::string body`: Request body.

**Namespaces:**
- `RequestHelper`: Contains helper functions for parsing requests.

**Functions:**
- [`RequestHelper::requestInfo ParseRequest(const std::string& buffer)`](../include/server/request.h): Parses the request buffer into a structured format.
- [`RequestHelper::requestInfo ParseRequestType(const std::string& buffer)`](../include/server/request.h): Parses the request type from the buffer.

#### Response
Defined in [`include/server/response.h`](../include/server/response.h)

**Public Methods:**
- [`Response(int SocketId, int ClientSock)`](../include/server/response.h): Constructor to initialize the response.
- [`void SetContentType(Enums::CONTENT_TYPE content_type)`](../include/server/response.h): Sets the content type of the response.
- [`void SetStatus(const std::string& status)`](../include/server/response.h): Sets the HTTP status of the response.
- [`void SetBody(const std::string& nBody)`](../include/server/response.h): Sets the body of the response.
- [`void Send()`](../include/server/response.h): Sends the response to the client.

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
Defined in [`include/server/router.h`](../include/server/router.h)

**Public Methods:**
- [`Router()`](../include/server/router.h): Constructor for the router.
- [`void Get(const std::string& Path, ListenerHelper::callback_function func)`](../include/server/router.h): Registers a GET route with the specified path and callback function.
- [`void GetStatic(const std::string& Path, ListenerHelper::callback_function_static func, serve_static::StaticFile file)`](../include/server/router.h): Registers a static file handler for HTTP GET requests.

#### FileParser
Defined in [`include/server/file_parser.h`](../include/server/file_parser.h)

**Public Methods:**
- [`static std::string GetHTMLPage(const std::string& path)`](../include/server/file_parser.h): Reads an HTML file from the given path and returns its contents as a string.
- [`static std::string GetFileContents(const std::string& path)`](../include/server/file_parser.h): Reads the contents of a file and returns it as a string.
- [`static bool IsFileOfType(std::string filename, std::string extension)`](../include/server/file_parser.h): Checks if the given filename has the specified extension.

#### StringUtils
Defined in [`include/server/string_utils.h`](../include/server/string_utils.h)

**Public Methods:**
- [`static bool Contains(const std::string& str, const std::string& substr)`](../include/server/string_utils.h): Checks if a string contains a substring.

#### Constants
Defined in [`include/server/constants.h`](../include/server/constants.h)

**Members:**
- `char HTTP_GET[3]`: HTTP GET method.
- `char HTTP_POST[4]`: HTTP POST method.

**Enums:**
- [`typedef char HTTP_STATUS[14]`](../include/server/constants.h): HTTP status type.
- [`typedef std::string CONTENT_TYPE`](../include/server/constants.h): Content type.
- [`int HTTP_G`](../include/server/constants.h): HTTP GET enum.
- [`int HTTP_P`](../include/server/constants.h): HTTP POST enum.
- [`int HTTP_PU`](../include/server/constants.h): HTTP PUT enum.
- [`HTTP_STATUS HTTP_OK`](../include/server/constants.h): HTTP 200 OK status.
- [`CONTENT_TYPE TEXT_PLAIN`](../include/server/constants.h): Plain text content type.
- [`CONTENT_TYPE TEXT_HTML`](../include/server/constants.h): HTML content type.
- [`CONTENT_TYPE TEXT_JSON`](../include/server/constants.h): JSON content type.
- [`CONTENT_TYPE TEXT_CSS`](../include/server/constants.h): CSS content type.
- [`HTTP_STATUS HTTP_NOTFOUND`](../include/server/constants.h): HTTP 404 Not Found status.
- [`typedef int HTTP_METHOD`](../include/server/constants.h): HTTP method type.

## Usage
1. Define routes using the [`Server::Get`](../include/server/server.h) method.
2. Start the server using the [`Server::Start`](../include/server/server.h) method.
3. Handle client requests and send responses using the [`Request`](../include/server/request.h) and [`Response`](../include/server/response.h) classes.

## Building and Running
To build and run the project, follow these steps:

1. Open a terminal and navigate to the project directory.
2. Run the build script:
    ```sh
    ./build.sh
    ```
3. Run the compiled executable:
    ```sh
    ./build/server
    ```

The server will start and listen for incoming connections on the specified port.

---

This documentation provides an overview of the project's structure, classes, and functions. For more detailed information, refer to the source code files.
