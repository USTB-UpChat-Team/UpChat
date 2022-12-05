#
# UpChat - CMake 项目主文件
# 作者：刘新宇  2022.12.4
#

cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 17)

set_property(GLOBAL PROPERTY USE_FOLDERS FORCE)

set(UPCHAT_VERSION_MAJOR 0)
set(UPCHAT_VERSION_MINOR 0)
set(UPCHAT_VERSION_PATCH 1)

set(UPCHAT_VERSION ${UPCHAT_VERSION_MAJOR}.${UPCHAT_VERSION_MINOR}.${UPCHAT_VERSION_PATCH})
project("UpChat" VERSION ${UPCHAT_VERSION} LANGUAGES CXX)

add_subdirectory(ThirdParty)
add_subdirectory(UpChat)

add_executable(UpChatTest "UpChatTest.cpp")
target_link_libraries(UpChatTest UpChatCore UpChatServer WS2_32)
