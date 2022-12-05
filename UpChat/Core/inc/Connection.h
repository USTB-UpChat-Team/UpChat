/**
 * @file        Connection.h
 * @author      刘新宇 (liuxinyu0112@outlook.com)
 * @brief       SSL
 * @version     0.0.1
 * @date        2022-12-04
 * 
 * @copyright   Copyright (C) Liu Xinyu 2022, all rights reserved.
 * 
 */

#pragma once

#include "PlatformAPI.h"
#include "Socket.h"

#include <openssl/ssl.h>
#include <Connection.h>

namespace UpChat::Net
{
    class CSSLContext;
    /**
     * @brief SSL 连接
     */
    class CSSLConnection
    {
    public:
        /**
         * @brief 初始化为 SSL 服务端
         * 
         * @param CertificateFile   证书文件
         * @param PrivateKeyFile    私钥文件
         * @param Password          证书密码
         */
        UCRESULT InitializeAsServer(const char* CertificateFile, const char* PrivateKeyFile, char* Password = nullptr);
        UCRESULT Accept(UCSOCKET Socket, CSSLContext** pContext);
        
        /**
         * @brief 初始化为 SSL 客户端
         */
        UCRESULT InitializeAsClient();
        UCRESULT Connect(UCSOCKET Socket, CSSLContext** pContext);

        void Free();

    private:

        void Initialize();

        SSL_CTX* m_CTX;
    };

    class CSSLContext
    {
    public:

        CSSLContext() : m_SSL(nullptr) {}

        /**
         * @brief 接受消息
         *
         * @param Buffer    消息数据
         * @param Size      消息长度
         */
        int Read(void* Buffer, int Size);

        /**
         * @brief 发送消息
         *
         * @param Buffer    消息数据
         * @param Size      消息长度
         */
        int Write(void* Buffer, int Size);

        UCRESULT Shutdown();


    private:
        friend class CSSLConnection;
        SSL* m_SSL;
    };
} // namespace UpChat::Net
