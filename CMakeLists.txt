cmake_minimum_required(VERSION 3.16)
project(udp_communication)

add_compile_options(-Wall)
set(CMAKE_BUILD_TYPE Debug)  # Debug | RelWithDebInfo | Release

find_package(Threads REQUIRED)
find_package(Boost REQUIRED COMPONENTS system)

# -------------------------------------------------------------------------------
# Build
# -------------------------------------------------------------------------------

# Client
add_executable(client
        src/client.cpp
        src/protocol.cpp
        )
target_include_directories(client PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        )
target_link_libraries(client PUBLIC
        Threads::Threads
        Boost::system
        )

# Server
add_executable(server
        src/server.cpp
        src/protocol.cpp
        )
target_include_directories(server PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        )
target_link_libraries(server PUBLIC
        Threads::Threads
        Boost::system
        )

# -------------------------------------------------------------------------------
# Install
# -------------------------------------------------------------------------------
install(
        TARGETS
        client server
        DESTINATION bin
        )
