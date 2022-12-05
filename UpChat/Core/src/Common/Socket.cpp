/**
 * @file        Socket.cpp
 * @author      刘新宇 (liuxinyu0112@outlook.com)
 * @brief       嵌套字
 * @version     0.0.1
 * @date        2022-12-04
 * 
 * @copyright   Copyright (C) Liu Xinyu 2022, all rights reserved.
 * 
 */

#include "Socket.h"

#include <cassert>
#include <stdexcept>

#ifdef _MSC_VER
#include <WinSock2.h>
#include <WS2tcpip.h>
#else
#endif

namespace UpChat::Net
{
    namespace Internal
    {
        //
        class CSocket : public ISocket
        {
        public:

            CSocket(const SocketInfo& Info)
            {
#ifdef _MSC_VER
                WORD versionRequired = MAKEWORD(1, 1);
                WSADATA wsaData = {};
                if (::WSAStartup(versionRequired, &wsaData))
                {
                    throw std::runtime_error("WSAStartup() Failed");
                }
#endif
                //
                m_Socket = (UCSOCKET)::socket(AF_INET, SOCK_STREAM, 0);
                //
                if (m_Socket == -1) throw std::runtime_error("socket() Failed");
                //
                sockaddr_in a = {};
                a.sin_family = AF_INET;
                ::inet_pton(AF_INET, Info.Address, &a.sin_addr);
                a.sin_port = ::htons(Info.Port);
                //
                if (Info.Type == SocketType::Server)
                    if (bind(m_Socket, (sockaddr*)&a, sizeof(sockaddr_in)))
                        throw std::runtime_error("bind() Failed");

                m_Type = Info.Type;
            }

            UPCHAT_DECLARE_FUNCTION(UCRESULT, Listen, (int Backlog))
            {
                assert(m_Type == SocketType::Server);
                return ::listen(m_Socket, Backlog);
            }

            UPCHAT_DECLARE_FUNCTION(UCSOCKET, Accept, (SocketInfo& Info))
            {
                assert(m_Type == SocketType::Server);
                sockaddr_in a = {};
                int len = sizeof(sockaddr_in);
                UCSOCKET s = (UCSOCKET)::accept(m_Socket, (sockaddr*)&a, &len);
                //
                ::inet_ntop(AF_INET, &a.sin_addr, Info.Address, sizeof(SocketInfo::Address));
                Info.Port = ::htons(a.sin_port);
                //
                return s;
            }

            UPCHAT_DECLARE_FUNCTION(UCRESULT, Connect, (const SocketInfo& Info))
            {
                assert(m_Type == SocketType::Client);
                sockaddr_in a = {};
                a.sin_family = AF_INET;
                ::inet_pton(AF_INET, Info.Address, &a.sin_addr);
                a.sin_port = ::htons(Info.Port);
                //
                return ::connect(m_Socket, (sockaddr*)&a, sizeof(sockaddr_in));
            }

            UPCHAT_DECLARE_FUNCTION(UCRESULT, Close, ())
            {
                return ::closesocket(m_Socket);
            }

            UPCHAT_DECLARE_FUNCTION(UCRESULT, GetSocket, () const)
            {
                return m_Socket;
            }

            UPCHAT_DECLARE_FUNCTION(UCRESULT, Cleanup, ())
            {
#ifdef _MSC_VER
                return ::WSACleanup();
#endif
                return 0;
            }

        private:
            SocketType  m_Type;
            UCSOCKET    m_Socket;
        };
    } // namespace Internal
    
    UPCHAT_DECLARE_API_FUNCTION(std::unique_ptr<ISocket>, CreateSocket, (const SocketInfo& Info))
    {
        return std::unique_ptr<ISocket>(new Internal::CSocket(Info));
    }
} // namespace UpChat::Net
