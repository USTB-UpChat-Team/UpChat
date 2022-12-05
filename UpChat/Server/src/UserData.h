/**
 * @file        UserData.h
 * @author      刘新宇 (liuxinyu0112@outlook.com)
 * @brief       用户信息
 * @version     0.0.1
 * @date        2022-12-04
 * 
 * @copyright   Copyright (C) Liu Xinyu 2022, all rights reserved.
 * 
 */

#pragma once

#include <string>

namespace UpChat
{
    struct UserData
    {
        std::string Username;
        std::string Password;
        std::string Friends;
    };
} // namespace UpChat
