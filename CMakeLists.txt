cmake_minimum_required(VERSION 3.13)
project(SimpleGF_Test)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

include_directories(./src)

file(GLOB sourcefiles "./src/*.cpp")

add_executable(SimpleGF_Test
    ${sourcefiles}
    )

target_link_libraries(SimpleGF_Test
    GL
    GLEW
    glfw
    )
