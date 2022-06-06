add_library(
    CLI SHARED
    cli.cpp
)

target_include_directories(CLI PUBLIC "${PROJECT_SOURCE_DIR}/lib/Pop3Session")
target_include_directories(CLI PUBLIC "${PROJECT_SOURCE_DIR}/lib/Error")
target_include_directories(CLI PUBLIC "${PROJECT_SOURCE_DIR}/lib/Base64Codec")
target_include_directories(CLI PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/")