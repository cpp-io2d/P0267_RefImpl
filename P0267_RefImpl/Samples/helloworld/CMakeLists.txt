cmake_minimum_required(VERSION 3.8.0)
set(CMAKE_CXX_STANDARD 17)

# Use the CMakeLists.txt's parent-directory-name for the project's id/name
get_filename_component(PROJECT_ID ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" PROJECT_ID ${PROJECT_ID})
project(${PROJECT_ID})

add_executable(${PROJECT_ID} main.cpp)
target_link_libraries(${PROJECT_ID} io2d)

if(MSVC)
	target_compile_definitions(${PROJECT_ID} PUBLIC -DUNICODE -D_UNICODE -D_CRT_SECURE_NO_WARNINGS)
	target_link_options(${PROJECT_ID} PUBLIC -SUBSYSTEM:WINDOWS -ENTRY:mainCRTStartup)
endif()

