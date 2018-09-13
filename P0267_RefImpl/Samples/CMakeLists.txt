cmake_minimum_required(VERSION 3.0.0)
project(io2d CXX)

# Search for and add sample app(s):
file(GLOB all_paths ${CMAKE_CURRENT_LIST_DIR}/*)
set(all_samples "")
foreach(one_path ${all_paths})
    if(IS_DIRECTORY ${one_path})
        if(EXISTS ${one_path}/CMakeLists.txt)
            get_filename_component(one_sample ${one_path} NAME)
            add_subdirectory(${one_sample})
        endif()
    endif()
endforeach()
