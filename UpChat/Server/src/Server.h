/**
 * @file        Server.h
 * @author      刘新宇 (liuxinyu0112@outlook.com)
 * @brief       服务器
 * @version     0.0.1
 * @date        2022-12-04
 * 
 * @copyright   Copyright (C) Liu Xinyu 2022, all rights reserved.
 * 
 */

#pragma once

#include "Connection.h"
#include "PingPong.h"

#include <unordered_map>
#include <string>

namespace UpChat
{
    class CServerMain
    {
    public:

        CServerMain(const char* Address, unsigned short Port, const char* Certificate, const char* PrivateKey, char* Password);

        void Run();

    private:

        std::unique_ptr<Net::ISocket>           m_ServerSocket;
        std::unique_ptr<Net::CSSLConnection>    m_ServerConnection;

        UCRESULT Login(const Net::LoginData& Data);
        UCRESULT SignUp(const Net::SignUpData& Data);

        void SendTo(const Net::ChatData& Data);

        struct ConnectionObject
        {
            std::unique_ptr<Net::ISocket>       Socket;
            std::unique_ptr<Net::CSSLContext>   Context;
        };

        std::unordered_map<std::string, Net::CSSLContext*> m_Connections;
    };
} // namespace UpChat
