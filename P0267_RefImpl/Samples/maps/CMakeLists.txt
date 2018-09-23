cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 17)

find_package(Boost 1.67.0 QUIET COMPONENTS system date_time)

if( NOT Boost_FOUND )
    message( "Skipping the Maps example since Boost was not found" )
    return()
endif()

find_package(OpenSSL QUIET)
if( NOT OPENSSL_FOUND )
    message( "Skipping the Maps example since OpenSSL was not found" )
    return()
endif()

add_subdirectory(external/pugixml)

# Use the CMakeLists.txt's parent-directory-name for the project's id/name
get_filename_component(PROJECT_ID ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" PROJECT_ID ${PROJECT_ID})
project(${PROJECT_ID})

add_executable(${PROJECT_ID}
    main.cpp
    model.cpp
    model.h
    render.cpp
    render.h
    http.cpp
    http.h
)

target_link_libraries(${PROJECT_ID}
    io2d
    pugixml
    ${Boost_LIBRARIES}
    ${OPENSSL_LIBRARIES}
)
target_include_directories(${PROJECT_ID} SYSTEM
    PRIVATE ${Boost_INCLUDE_DIRS}
    PRIVATE ${OPENSSL_INCLUDE_DIR}
)

if( ${CMAKE_SYSTEM_NAME} MATCHES "Linux" )
    target_link_libraries(${PROJECT_ID} pthread)
endif()

if(MSVC)
	target_compile_options(${PROJECT_ID} PUBLIC /D_SILENCE_CXX17_ALLOCATOR_VOID_DEPRECATION_WARNING /wd4459)
endif()
