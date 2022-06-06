# create target
add_library(
    Socket
    socket.cpp
)

target_include_directories(Socket PUBLIC "${PROJECT_SOURCE_DIR}/lib/Error")
target_include_directories(Socket PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/")