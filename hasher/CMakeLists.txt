add_library(hasher INTERFACE)

target_include_directories(hasher INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/
)
target_link_libraries(hasher INTERFACE
    OpenSSL::Crypto
)
