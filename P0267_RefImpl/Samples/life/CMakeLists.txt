cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 17)

# Use the CMakeLists.txt's parent-directory-name for the project's id/name
get_filename_component(PROJECT_ID ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" PROJECT_ID ${PROJECT_ID})
project(${PROJECT_ID})

add_executable(${PROJECT_ID} main.cpp)
target_link_libraries(${PROJECT_ID} io2d)

if( DEFINED IOS_PLATFORM )
    # iOS requires special packaging, so we have to treat this target separately
    set_target_properties(${PROJECT_ID} PROPERTIES MACOSX_BUNDLE YES)
    set_target_properties(${PROJECT_ID} PROPERTIES MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/iOS/Info.plist")
    target_sources(${PROJECT_ID} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/iOS/LaunchScreen.storyboard)
    target_sources(${PROJECT_ID} PRIVATE iOS/libcxx_tmp_stubs.cpp)
    set_target_properties(${PROJECT_ID} PROPERTIES RESOURCE "${CMAKE_CURRENT_SOURCE_DIR}/iOS/LaunchScreen.storyboard")
    set_target_properties(${PROJECT_ID} PROPERTIES XCODE_ATTRIBUTE_TARGETED_DEVICE_FAMILY "1,2")
endif()
