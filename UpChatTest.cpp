#include "Connection.h"
#include "rapidjson/document.h"

#include <iostream>

#include "UpChat/Server/src/Server.h"

using namespace UpChat;

int main()
{
    CServerMain ss("127.0.0.1", 7838, "D:/cert/public-rsa.cer", "D:/cert/private-rsa.key", "XinyuNB666");

    ss.Run();

    return 0;
}
