cmake_minimum_required(VERSION 3.0.0)
project(pop3-client VERSION 0.1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file(Config.h.in Config.h)

include(CTest)
enable_testing()

# add Base 64 library
add_subdirectory(Base64Codec)
# add CLI library
add_subdirectory(CLI)
# add Authentication library
add_subdirectory(Authentication)

add_executable(pop3-client main.cpp)

target_link_libraries(pop3-client PUBLIC Base64Codec)
target_link_libraries(pop3-client PUBLIC CLI)
target_link_libraries(pop3-client PUBLIC Authentication)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

# add the binary tree to the search path for include files
target_include_directories(pop3-client PUBLIC
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}/Base64Codec"
    "${PROJECT_SOURCE_DIR}/CLI"
    "${PROJECT_SOURCE_DIR}/Authentication"
)
