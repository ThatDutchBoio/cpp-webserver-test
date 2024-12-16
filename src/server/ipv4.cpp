#include "../../include/server/ipv4.h"
#include <arpa/inet.h>

sockaddr_in createServerAddress(int port, const std::string& ip) {
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &serverAddr.sin_addr);
    return serverAddr;
}