#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <csignal>
#include <vector>
#include "include/server/server.h"
// #include "include/server/ipv4.h"
// #include "include/server/file_parser.h"
#include "include/server/router.h"
#include "include/server/constants.h"
#include "src/api/testing.cpp"
#include "src/server/server_lib.cpp"
sockaddr_in ServerAddr = serverlib::createServerAddress(8080, "87.106.130.229");
Server App(ServerAddr);
void handle_signal(int signal)
{
    std::cout << "Handling signal!!" << std::endl;
    App.Stop();
}

int main()
{
    signal(SIGABRT, handle_signal);

    App.Get("/", [](serverlib::Request Req, serverlib::Response Res){
        std::cout << "app.get('/'')" << std::endl;

        Res.SetStatus(serverlib::HTTP_OK);
        Res.SetContentType(serverlib::TEXT_HTML);
        Res.SetBody(file_parser::FileParser::GetHTMLPage("./public/index.html"));
        Res.Send();
    });

    App.Get("/testing", [](serverlib::Request Req, serverlib::Response Res) {
        Res.SetStatus(Enums::HTTP_OK);
        Res.SetContentType(Enums::TEXT_HTML);
        Res.SetBody("<h1>testing path lol lmao pls work</h1>");
        Res.Send();
    });

    serverlib::Router TestRouter = TestingApi::GetRouter();

    App.Use("/testing", TestRouter);
    App.Start();
}