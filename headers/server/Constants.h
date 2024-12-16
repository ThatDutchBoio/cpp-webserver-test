namespace Constants {
    char HTTP_GET[3] = { 'G', 'E', 'T' };
    char HTTP_POST[4] = { 'P', 'O', 'S', 'T' };
    
} 

namespace Enums{
    typedef char HTTP_STATUS[8];
    typedef std::string CONTENT_TYPE;
    int HTTP_G = 0;
    int HTTP_P = 1;
    int HTTP_PU = 2;
    HTTP_STATUS HTTP_OK = "200 OK";
    CONTENT_TYPE TEXT_PLAIN = "text/plain";
    CONTENT_TYPE TEXT_HTML = "text/html";
    CONTENT_TYPE TEXT_JSON = "text/json";

}