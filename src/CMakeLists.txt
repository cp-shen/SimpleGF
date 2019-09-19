#cmake file for SimpleGF source dir

file(GLOB_RECURSE sourcefiles "*.cpp")

add_library(SimpleGF SHARED
    ${sourcefiles})

target_include_directories(SimpleGF
    PUBLIC ${SimpleGF_SOURCE_DIR}/include)

target_link_libraries(SimpleGF
    PUBLIC GL
    PUBLIC GLEW
    PUBLIC glfw
    )
