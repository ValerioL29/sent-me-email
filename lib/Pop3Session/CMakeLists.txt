add_library(
    Pop3Session SHARED
    pop3session.cpp
)

target_include_directories(Pop3Session PUBLIC "${PROJECT_SOURCE_DIR}/lib/Socket")
target_include_directories(Pop3Session PUBLIC "${PROJECT_SOURCE_DIR}/lib/Error")
target_include_directories(Pop3Session PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/")