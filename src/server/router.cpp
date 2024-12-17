#include "../../include/server/router.h"

Router::Router::Router() {}

void Router::Router::Get(const std::string& Path, callback_function func) {
    ListenerHelper::Listener nListener;
    nListener.Callback = func;
    nListener.Path = Path;
    nListener.Method = Enums::HTTP_GET;
    this->Listeners.push_back(nListener);
}