find_package(nlohmann_json)
find_package(OpenSSL)

add_library(hasher INTERFACE)

target_include_directories(hasher INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/
)
target_link_libraries(hasher INTERFACE
    OpenSSL::Crypto
    nlohmann_json::nlohmann_json
)

add_library(hmac INTERFACE)

target_include_directories(hmac INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/
)
target_link_libraries(hmac INTERFACE
    OpenSSL::Crypto
    hasher
)


add_library(pbkdf2 INTERFACE)

target_include_directories(pbkdf2 INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/)

target_link_libraries(pbkdf2 INTERFACE
    OpenSSL::Crypto
    hmac
)