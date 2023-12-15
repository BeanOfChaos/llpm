cmake_minimum_required(VERSION 3.26)
project(cprac VERSION 1.0
							DESCRIPTION "things"
							LANGUAGES CXX
				)

include(FindOpenSSL)

set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")
set(CMAKE_GENERATOR Ninja)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-O2 -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror")

add_subdirectory(crypto)

add_executable(main main.cpp)
target_compile_definitions(main PRIVATE
	OPENSSL_NO_DEPRECATED
	OPENSSL_API_COMPAT=30000
)
target_link_libraries(main PUBLIC
	PRIVATE hasher
)
target_compile_options(main PRIVATE
)
