#cmake file for SimpleGF tests

file(GLOB_RECURSE sourcefiles "./src/*.cpp")

add_executable(SimpleGF_Test
    ${sourcefiles})

target_link_libraries(SimpleGF_Test
    PRIVATE SimpleGF)
