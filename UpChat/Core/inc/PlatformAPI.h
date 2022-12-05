/**
 * @file        PlatformAPI.h
 * @author      刘新宇 (liuxinyu0112@outlook.com)
 * @brief       API
 * @version     0.0.1
 * @date        2022-12-04
 * 
 * @copyright   Copyright (C) Liu Xinyu 2022, all rights reserved.
 * 
 */

#pragma once

#define UPCHAT_ATTR
#define UPCHAT_API

#define UPCHAT_DECLARE_API_FUNCTION(type, name, param)      \
    UPCHAT_ATTR type UPCHAT_API name param

#define UPCHAT_DECLARE_INTERFACE_FUNCTION(type, name, param)    \
    virtual type name param = 0

#define UPCHAT_DECLARE_FUNCTION(type, name, param)  \
    type name param

namespace UpChat
{
    using UCRESULT = long;
    using UCSOCKET = int;
} // namespace UpChat
