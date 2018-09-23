cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 17)

# Use the CMakeLists.txt's parent-directory-name for the project's id/name
get_filename_component(PROJECT_ID ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" PROJECT_ID ${PROJECT_ID})
project(${PROJECT_ID})

add_executable(${PROJECT_ID} main.cpp)

target_link_libraries(${PROJECT_ID} io2d)

set(RSC_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/texture.jpg)
set(RSC_TARGET $<TARGET_FILE_DIR:${PROJECT_ID}>/texture.jpg)

add_custom_command( TARGET ${PROJECT_ID} POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy "${RSC_SOURCE}" "${RSC_TARGET}")

if(MSVC)
    set_target_properties(${PROJECT_ID} PROPERTIES  VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/$(Configuration)")
endif()
