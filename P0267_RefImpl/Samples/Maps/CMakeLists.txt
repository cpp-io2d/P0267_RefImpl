cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 17)

find_package(Boost QUIET COMPONENTS system)
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

project(maps)
add_executable(maps
    main.cpp
    model.cpp
    model.h
    render.cpp
    render.h
    http.cpp
    http.h
)
target_link_libraries(maps
    io2d
    pugixml
    ${Boost_LIBRARIES}
    ${OPENSSL_LIBRARIES}
)
target_include_directories(maps SYSTEM
    PRIVATE ${Boost_INCLUDE_DIRS}
    PRIVATE ${OPENSSL_INCLUDE_DIR}
)
