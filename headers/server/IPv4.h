#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>

// Simplified version of sockaddr_in
sockaddr_in createServerAddress(int port, const char *ip) {
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    inet_aton(ip, &serverAddr.sin_addr);
    return serverAddr;
}