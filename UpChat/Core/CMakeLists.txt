#
#
#
#

cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 17)

Project("UpChatCore")

set(UC_INCLUDE_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/inc)
set(UC_SOURCE_DIR   ${CMAKE_CURRENT_SOURCE_DIR}/src)

file(GLOB_RECURSE UC_HEADERS ${UC_INCLUDE_DIR}/*.*)
file(GLOB_RECURSE UC_SOURCES ${UC_SOURCE_DIR}/Common/*.* ${UC_SOURCE_DIR}/${UC_TARGET_PLATFORM}/*.*)

add_library("UpChatCore" ${UC_HEADERS} ${UC_SOURCES})
target_include_directories("UpChatCore" PUBLIC ${UC_INCLUDE_DIR})
target_link_libraries("UpChatCore" libssl libcrypto rapidjson)
