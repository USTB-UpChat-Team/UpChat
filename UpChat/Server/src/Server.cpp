/**
 * @file        Server.cpp
 * @author      刘新宇 (liuxinyu0112@outlook.com)
 * @brief       服务器
 * @version     0.0.1
 * @date        2022-12-04
 * 
 * @copyright   Copyright (C) Liu Xinyu 2022, all rights reserved.
 * 
 */

#include "Server.h"

namespace UpChat
{
	CServerMain::CServerMain(const char* Address, unsigned short Port, const char* Certificate, const char* PrivateKey, char* Password)
	{
		Net::SocketInfo info = {};
		info.Type = Net::SocketType::Server;
		strcpy(info.Address, Address);
		info.Port = Port;
		m_ServerSocket = Net::CreateSocket(info);

		m_ServerConnection = std::unique_ptr<Net::CSSLConnection>(new Net::CSSLConnection);
		m_ServerConnection->InitializeAsServer(Certificate, PrivateKey, Password);
	}

	void CServerMain::Run()
	{
		bool running = true;
		rapidjson::Document d;
		while (running)
		{
			m_ServerSocket->Listen(5);

			Net::SocketInfo info = {};
			auto socket = m_ServerSocket->Accept(info);

			Net::CSSLContext* pContext = nullptr;
			m_ServerConnection->Accept(socket, &pContext);

			char buffer[1024] = {};
			pContext->Read(buffer, 1024);

			d.Parse(buffer);
			
			rapidjson::Value magic;
			if (magic.GetInt() == (int)Net::PingMagic::Login)
			{
				rapidjson::Value username, password;
				username = d["username"];
				password = d["password"];

				if (m_Connections.find(username.GetString()) != m_Connections.end())
				{
					// TODO: 用户已经登录
					continue;
				}

				Net::LoginData ld = {};
				ld.Username = username.GetString();
				ld.Password = password.GetString();
				if (Login(ld))
				{
					// TODO: 密码不正确
					continue;
				}

				m_Connections.insert(std::make_pair(ld.Username, pContext));
			}
			else if (magic.GetInt() == (int)Net::PingMagic::Signup)
			{
				// TODO: 注册
			}
		}
	}

	UCRESULT CServerMain::Login(const Net::LoginData& Data)
	{
		return 0;
	}

	UCRESULT CServerMain::SignUp(const Net::SignUpData& Data)
	{
		return 0;
	}

	void CServerMain::SendTo(const Net::ChatData& Data)
	{
	}
} // namespace UpChat
