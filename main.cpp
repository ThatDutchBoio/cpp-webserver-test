#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <csignal>
#include <vector>
#include "include/server/server.h"
#include "include/server/ipv4.h"
#include "include/server/file_parser.h"
#include "include/server/router.h"
#include "include/server/constants.h"

sockaddr_in ServerAddr = createServerAddress(8080, "87.106.130.229");
Server App(ServerAddr);

void handle_signal(int signal)
{
    std::cout << "Handling signal!!" << std::endl;
    App.Stop();
}

int main()
{
    signal(SIGABRT, handle_signal);

    

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