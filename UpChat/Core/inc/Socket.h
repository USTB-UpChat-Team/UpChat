/**
 * @file        Socket.h
 * @author      刘新宇 (liuxinyu0112@outlook.com)
 * @brief       嵌套字 (Socket)
 * @version     0.0.1
 * @date        2022-12-04
 * 
 * @copyright   Copyright (C) Liu Xinyu 2022, all rights reserved.
 * 
 */

#pragma once

#include "PlatformAPI.h"

#include <memory>

namespace UpChat::Net
{
    enum class SocketType
    {
        Server,
        Client,
    };

    // IPv4
    struct SocketInfo
    {
        SocketType      Type;
        char            Address[16];
        unsigned short  Port;
    };

    //
    class ISocket
    {
    public:
        //
        UPCHAT_DECLARE_INTERFACE_FUNCTION(UCRESULT, Listen, (int Backlog));
        //
        UPCHAT_DECLARE_INTERFACE_FUNCTION(UCSOCKET, Accept, (SocketInfo& Info));
        //
        UPCHAT_DECLARE_INTERFACE_FUNCTION(UCRESULT, Connect, (const SocketInfo& Info));
        //
        UPCHAT_DECLARE_INTERFACE_FUNCTION(UCRESULT, Close, ());
        //
        UPCHAT_DECLARE_INTERFACE_FUNCTION(UCRESULT, GetSocket, () const);
        //
        UPCHAT_DECLARE_INTERFACE_FUNCTION(UCRESULT, Cleanup, ());
    };

    // IPv4
    UPCHAT_DECLARE_API_FUNCTION(std::unique_ptr<ISocket>, CreateSocket, (const SocketInfo& Info));
} // namespace UpChat::Net
