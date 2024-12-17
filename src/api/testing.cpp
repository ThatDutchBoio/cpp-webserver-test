// #include "../../include/server/router.h"
// #include "../../include/server/request.h"
// #include "../../include/server/response.h"
// #include "../../include/server/constants.h"
#include "../server/server_lib.cpp"




namespace TestingApi{
    serverlib::Router GetRouter(){
        serverlib::Router nRouter;

        nRouter.Get("/lol", [](serverlib::Request req, serverlib::Response res){
            res.SetContentType(Enums::TEXT_HTML);
            res.SetBody("<h1>Path: /testing/lol </h1>");
            res.SetStatus(Enums::HTTP_OK);
            res.Send();
        });


        return nRouter;
    }
}