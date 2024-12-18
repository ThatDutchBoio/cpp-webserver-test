#include "../../include/server/router.h"
#include "../../include/server/listener.h"
#include "../../include/server/static.h"

Router::Router::Router() {}

void Router::Router::Get(const std::string& Path, ListenerHelper::callback_function func) {
    ListenerHelper::Listener nListener;
    nListener.Callback = func;
    nListener.Path = Path;
    nListener.Method = Enums::HTTP_GET;
    this->Listeners.push_back(nListener);
}


Router::Router Router::Router::Serve_Static(serve_static::Static s){
    Router nRouter;


    
    return nRouter;
}