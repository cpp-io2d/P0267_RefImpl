cmake_minimum_required(VERSION 3.0.0)
project(io2d CXX)

if(EMSCRIPTEN)
	set(CMAKE_EXECUTABLE_SUFFIX ".html")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --shell-file ${CMAKE_CURRENT_SOURCE_DIR}/emscripten_template_page.html" )
endif()

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
