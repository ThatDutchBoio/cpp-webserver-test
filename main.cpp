#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <csignal>
#include <vector>
#include "src/api/testing.cpp"
#include "src/server/server_lib.cpp"
#include <chrono>

sockaddr_in ServerAddr = serverlib::createServerAddress(8080, "87.106.130.229");
Server App(ServerAddr);
void handle_signal(int signal)
{
    std::cout << "Handling signal!!" << std::endl;
    App.Stop();
}

int main()
{
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;
    auto t1 = high_resolution_clock::now();
    signal(SIGABRT, handle_signal);
    serverlib::Static s("/", "./public");

    App.Get("/", [](serverlib::Request& Req, serverlib::Response& Res){
        std::cout << "app.get('/'')" << std::endl;

        Res.SetStatus(serverlib::HTTP_OK);
        Res.SetContentType(serverlib::TEXT_HTML);
        Res.SetBody(file_parser::FileParser::GetHTMLPage("./public/index.html"));
        Res.Send();
    });

    App.Get("/testing", [](serverlib::Request& Req, serverlib::Response& Res) {
        Res.SetStatus(Enums::HTTP_OK);
        Res.SetContentType(Enums::TEXT_HTML);
        Res.SetBody("<h1>testing path lol lmao pls work</h1>");
        Res.Send();
    });
    serverlib::Router static_router = serverlib::Serve_Static(s);
    std::cout << "static router memaddr: " << &static_router << std::endl;
    App.Use("/", static_router);
    serverlib::Router TestRouter = TestingApi::GetRouter();

    App.Use("/testing", TestRouter);
    auto t2 = high_resolution_clock::now();
    /* Getting number of milliseconds as an integer. */
    auto ms_int = duration_cast<milliseconds>(t2 - t1);
    
    /* Getting number of milliseconds as a double. */
    duration<double, std::milli> ms_double = t2 - t1;
    std::cout << "Server intitialisation took: " << ms_int.count() << "ms" << std::endl;
    std::cout << "Server intitialisation took: " << ms_double.count() << "ms" << std::endl;
    return 0;
    App.Start();
}