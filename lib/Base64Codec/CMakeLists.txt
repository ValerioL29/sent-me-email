add_library(
    Base64Codec
    base64.cpp
)

target_include_directories(Base64Codec PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/")
