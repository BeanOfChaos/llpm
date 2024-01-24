find_package(nlohmann_json)

add_library(database STATIC
    database.cpp)

target_include_directories(database PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/
)
target_link_libraries(database PRIVATE
    hasher
    nlohmann_json::nlohmann_json
)