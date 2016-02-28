cmake_minimum_required(VERSION 2.8.12)

project(hello CXX)

add_executable(hello hello.cpp)

target_link_libraries(hello ${IO2D_LIBRARY})
target_include_directories(hello PRIVATE ${IO2D_INCLUDE_DIR})

if (WIN32)
    target_compile_definitions(hello PRIVATE
        CAIRO_WIN32_STATIC_BUILD _WIN32_WINNT=0x0600)
endif()
