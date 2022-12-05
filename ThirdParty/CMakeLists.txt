#
# UpChat - 第三方依赖
# 作者：刘新宇  2022.12.4
#

cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 17)

# RapidJSON
set(RAPIDJSON_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/rapidjson/include)
file(GLOB_RECURSE RAPIDJSON_SOURCES ${RAPIDJSON_INCLUDE_DIR}/*.*)
add_library(rapidjson INTERFACE)
target_sources(rapidjson INTERFACE ${RAPIDJSON_SOURCES})
target_include_directories(rapidjson INTERFACE ${RAPIDJSON_INCLUDE_DIR})
