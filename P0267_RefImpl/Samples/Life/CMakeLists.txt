cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 17)

project(life)
add_executable(life main.cpp)
target_link_libraries(life io2d)

if( DEFINED IOS_PLATFORM )
    # iOS requires special packaging, so we have to treat this target separately
    set_target_properties(life PROPERTIES MACOSX_BUNDLE YES)
    set_target_properties(life PROPERTIES MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/iOS/Info.plist")
    target_sources(life PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/iOS/LaunchScreen.storyboard)
    target_sources(life PRIVATE iOS/libcxx_tmp_stubs.cpp)
    set_target_properties(life PROPERTIES RESOURCE "${CMAKE_CURRENT_SOURCE_DIR}/iOS/LaunchScreen.storyboard")
    set_target_properties(life PROPERTIES XCODE_ATTRIBUTE_TARGETED_DEVICE_FAMILY "1,2")
endif()

if(EMSCRIPTEN)
	set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif()
