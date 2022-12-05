#
#
#
#

set(UC_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
file(GLOB_RECURSE UC_SOURCES ${UC_INCLUDE_DIR}/*.*)
add_library(UpChatServer ${UC_SOURCES})
target_link_libraries(UpChatServer UpChatCore)
