cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 17)
project(cpuload)

set(CPULOAD_SRC
    main.cpp
    data_source.cpp
    data_source.h
    profiler.h
)

if( ${CMAKE_SYSTEM_NAME} MATCHES "Darwin" )
    list(APPEND CPULOAD_SRC profiler_mach.cpp)
elseif( ${CMAKE_SYSTEM_NAME} MATCHES "Windows" )
    list(APPEND CPULOAD_SRC profiler_nt.cpp)
else()
    return()
endif()

add_executable(cpuload ${CPULOAD_SRC})
target_link_libraries(cpuload io2d)
