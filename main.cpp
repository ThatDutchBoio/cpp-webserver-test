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
#include "./headers/server/FileParser.h"

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

    App.Get("/", [](Request Req, Response Res){
        std::cout << "app.get('/'')" << std::endl;
        Res.SetStatus(Enums::HTTP_OK);
        Res.SetContentType(Enums::TEXT_HTML);
        Res.SetBody(FileParser::GetHTMLPage("./index.html"));
        Res.Send();
    });

    App.Get("/testing", [](Request Req, Response Res) {
        Res.SetStatus(Enums::HTTP_OK);
        Res.SetContentType(Enums::TEXT_HTML);
        Res.SetBody("<h1>testing path lol lmao pls work</h1>");
        Res.Send();
    });

    
    App.Start();

}
