cmake_minimum_required(VERSION 3.16)
project(udp_communication)

add_compile_options(-Wall)
set(CMAKE_BUILD_TYPE Debug)  # Debug | RelWithDebInfo | Release

find_package(Threads REQUIRED)

# -------------------------------------------------------------------------------
# Build
# -------------------------------------------------------------------------------

# Client
add_executable(client
        src/client.cpp
        )
target_link_libraries(
        client PUBLIC
        Threads::Threads
        )

# Server
add_executable(server
        src/server.cpp
        )
target_link_libraries(
        server PUBLIC
        Threads::Threads
        )

# -------------------------------------------------------------------------------
# Install
# -------------------------------------------------------------------------------
install(
        TARGETS
        client server
        DESTINATION bin
        )
