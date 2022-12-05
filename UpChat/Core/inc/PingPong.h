/**
 * @file        PingPong.h
 * @author      刘新宇 (liuxinyu0112@outlook.com)
 * @brief       通信
 * @version     0.0.1
 * @date        2022-12-04
 * 
 * @copyright   Copyright (C) Liu Xinyu 2022, all rights reserved.
 * 
 */

#pragma once

#include "PlatformAPI.h"
#include <rapidjson/document.h>

#include <string>

#define UC_PINGPONG_END_MAGIC  0xAFui8

namespace UpChat::Net
{
	enum class PingMagic
	{
        Login,
        Signup,
        Message,
	};

    enum class PongMagic
    {
        Status,
        Message,
    };

    struct LoginData
    {
        std::string Username;
        std::string Password;
    };

    using SignUpData = LoginData;

    struct ChatData
    {
        std::string Username;
        std::string Message;
    };
} // namespace UpChat::Net
