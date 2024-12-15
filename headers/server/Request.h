#include <vector>
#include <arpa/inet.h>

struct RequestHeaders {
    char Accept[32];
    char UserAgent[64];
    char Authorization[128];
    char ContentType[32];
    char Cookie[32];
};

class Request{
    public:
    int RequestMethod;
    char Path[256];
    sockaddr_in Source_Address;
    char body[1024];

};

namespace RequestHelper{
    typedef std::vector<std::vector<char>> requestInfo;

    requestInfo ParseRequest(char buffer[1024]){
        std::vector<std::vector<char>> request;
        std::vector<char> line;
        for (int i = 0; i < 1024; i++){
            if (buffer[i] == '\n'){
                request.push_back(line);
                line.clear();
            } else {
                line.push_back(buffer[i]);
            }
        }
        return request;
    }
   requestInfo ParseRequestType(std::vector<char> buffer){
         std::vector<std::vector<char>> requestType;
         std::vector<char> line;
         for (int i = 0; i < 1024; i++){
              if (buffer[i] == ' '){
                requestType.push_back(line);
                line.clear();
              } else {
                line.push_back(buffer[i]);
              }
         }
        return requestType;
   }

   

}

