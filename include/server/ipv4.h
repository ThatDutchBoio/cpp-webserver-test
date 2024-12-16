#pragma once
#include <netinet/in.h>
#include <string>

/**
 * @brief Creates a sockaddr_in structure for a server address.
 * 
 * This function initializes a sockaddr_in structure with the specified
 * port number and IP address, which can be used to bind a socket to
 * a specific address and port.
 * 
 * @param port The port number to bind the server to.
 * @param ip The IP address to bind the server to, in string format.
 * @return A sockaddr_in structure initialized with the specified port and IP address.
 */
sockaddr_in createServerAddress(int port, const std::string& ip);