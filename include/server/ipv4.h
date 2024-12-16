#pragma once
#include <netinet/in.h>
#include <string>

sockaddr_in createServerAddress(int port, const std::string& ip);