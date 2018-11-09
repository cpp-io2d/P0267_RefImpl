cmake_minimum_required(VERSION 3.0.0)
get_filename_component(SAMPLE_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
get_filename_component(PROJ_DIR ${SAMPLE_DIR} DIRECTORY)
get_filename_component(TOP_DIR ${PROJ_DIR} DIRECTORY)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${TOP_DIR}/cmake)
set(CMAKE_CXX_STANDARD 17)


set(PROJECT_ID maps)
project(${PROJECT_ID})

find_package(Boost 1.67.0 QUIET COMPONENTS system date_time)
find_package(io2d REQUIRED)
find_package(Cairo) 
find_package(GraphicsMagick) 


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
#get_filename_component(PROJECT_ID ${CMAKE_CURRENT_SOURCE_DIR} NAME)
#string(REPLACE " " "_" PROJECT_ID ${PROJECT_ID})
#project(${PROJECT_ID})

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
    PRIVATE io2d::io2d
    pugixml
    ${Boost_LIBRARIES}
    ${OPENSSL_LIBRARIES}
)
target_include_directories(${PROJECT_ID} SYSTEM
    PRIVATE ${Boost_INCLUDE_DIRS}
    PRIVATE ${OPENSSL_INCLUDE_DIR}
)

if( ${CMAKE_SYSTEM_NAME} MATCHES "Linux" )
    target_link_libraries(${PROJECT_ID} PUBLIC pthread)
endif()

if(MSVC)
	target_compile_options(${PROJECT_ID} PUBLIC /D_SILENCE_CXX17_ALLOCATOR_VOID_DEPRECATION_WARNING /wd4459)
endif()
