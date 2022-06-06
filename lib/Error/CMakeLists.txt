add_library(
    Error SHARED
    error.cpp
)

target_include_directories(Error PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/")