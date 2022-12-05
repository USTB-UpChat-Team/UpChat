/**
 * @file        Connection.cpp
 * @author      刘新宇 (liuxinyu0112@outlook.com)
 * @brief       SSL 连接
 * @version     0.0.1
 * @date        2022-12-04
 * 
 * @copyright   Copyright (C) Liu Xinyu 2022, all rights reserved.
 * 
 */

#pragma once

#include "Connection.h"

namespace UpChat::Net
{
	void CSSLConnection::Initialize()
	{
		//
		SSL_library_init();
		//
		OpenSSL_add_all_algorithms();
		//
		SSL_load_error_strings();
	}

	UCRESULT CSSLConnection::InitializeAsServer(const char* CertificateFile, const char* PrivateKeyFile, char* Password)
	{
		Initialize();

		//
		m_CTX = SSL_CTX_new(SSLv23_server_method());
		//
		if (!m_CTX) return 1;

		//
		if (::SSL_CTX_use_certificate_file(m_CTX, CertificateFile, SSL_FILETYPE_PEM) <= 0) return 2;

		//
		if (Password)
		{
			::SSL_CTX_set_default_passwd_cb_userdata(m_CTX, Password);
		}

		//
		if (::SSL_CTX_use_PrivateKey_file(m_CTX, PrivateKeyFile, SSL_FILETYPE_PEM) <= 0) return 3;

		//
		if (!::SSL_CTX_check_private_key(m_CTX)) return 4;

		return 0;
	}

	UCRESULT CSSLConnection::Accept(UCSOCKET Socket, CSSLContext** ppContext)
	{
		auto pContext = new CSSLContext;
		*ppContext = pContext;
		// 基于 CTX 创建一个新的 SSL
		pContext->m_SSL = ::SSL_new(m_CTX);
		// 将连接用户的嵌套字加入到 SSL
		::SSL_set_fd(pContext->m_SSL, Socket);
		// 建立 SSL 连接
		return ::SSL_accept(pContext->m_SSL);
	}

	UCRESULT CSSLConnection::InitializeAsClient()
	{
		Initialize();
		//
		m_CTX = SSL_CTX_new(SSLv23_client_method());

		//
		if (!m_CTX) return 1;
	}

	UCRESULT CSSLConnection::Connect(UCSOCKET Socket, CSSLContext** ppContext)
	{
		auto pContext = new CSSLContext;
		*ppContext = pContext;
		// 基于 CTX 创建一个新的 SSL
		pContext->m_SSL = ::SSL_new(m_CTX);
		// 将连接用户的嵌套字加入到 SSL
		::SSL_set_fd(pContext->m_SSL, Socket);
		//
		return ::SSL_connect(pContext->m_SSL);
	}

	void CSSLConnection::Free()
	{
		::SSL_CTX_free(m_CTX);
	}

	int CSSLContext::Read(void* Buffer, int Size)
	{
		return ::SSL_read(m_SSL, Buffer, Size);
	}

	int CSSLContext::Write(void* Buffer, int Size)
	{
		return ::SSL_write(m_SSL, Buffer, Size);
	}

	UCRESULT CSSLContext::Shutdown()
	{
		int r = ::SSL_shutdown(m_SSL);
		::SSL_free(m_SSL);
		return r;
	}
} // namespace UpChat::Net
