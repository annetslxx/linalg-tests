cmake_minimum_required(VERSION 3.22.1)
project(linalg_tests)
set(CMAKE_CXX_STANDARD 17)

file(GLOB my_source source/*.cpp)
add_subdirectory(linalg)

add_subdirectory(googletest)

add_executable(tests ${my_source})

if(WIN32)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()

target_link_libraries(tests PUBLIC
        linalg
        gtest
        gtest_main
)
