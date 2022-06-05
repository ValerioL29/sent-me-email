# create target
add_library(
    Socket SHARED
    socket.cpp
)

target_include_directories(Socket PUBLIC "../Error/")
target_include_directories(Socket PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/")