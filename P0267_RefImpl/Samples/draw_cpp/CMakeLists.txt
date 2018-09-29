cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 17)

# Use the CMakeLists.txt's parent-directory-name for the project's id/name
get_filename_component(PROJECT_ID ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" PROJECT_ID ${PROJECT_ID})
project(${PROJECT_ID})

add_executable(${PROJECT_ID} main.cpp)

target_link_libraries(${PROJECT_ID} io2d)

# If std::filesystem is not available, use boost::filesystem
include(CheckIncludeFileCXX)
CHECK_INCLUDE_FILE_CXX(filesystem STD_FILESYSTEM_INCLUDED)
if (NOT STD_FILESYSTEM_INCLUDED)
    find_package(Boost REQUIRED COMPONENTS system filesystem)
    target_include_directories(${PROJECT_ID} PRIVATE ${Boost_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_ID} ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY})
endif()

set(RSC_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/texture.jpg)
set(RSC_TARGET $<TARGET_FILE_DIR:${PROJECT_ID}>/texture.jpg)

add_custom_command( TARGET ${PROJECT_ID} POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy "${RSC_SOURCE}" "${RSC_TARGET}")

if(MSVC)
    set_target_properties(${PROJECT_ID} PROPERTIES  VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/$(Configuration)")
endif()
