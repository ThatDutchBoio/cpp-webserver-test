#include "../../include/server/router.h"

Router::Router() {}

void Router::Get(const std::string& Path, callback_function func) {
    Listener nListener;
    nListener.Callback = func;
    nListener.Path = Path;
    nListener.Method = Enums::HTTP_GET;
    this->Listeners.push_back(nListener);
}