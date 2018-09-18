cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 17)

# Use the CMakeLists.txt's parent-directory-name for the project's id/name
get_filename_component(PROJECT_ID ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" PROJECT_ID ${PROJECT_ID})
project(${PROJECT_ID})

add_executable(${PROJECT_ID} main.cpp)
target_link_libraries(${PROJECT_ID} io2d)

add_custom_command( TARGET ${PROJECT_ID} POST_BUILD
 COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/cat.jpg" "$<TARGET_FILE_DIR:${PROJECT_ID}>/cat.jpg"
)

if(MSVC)
	set_target_properties(${PROJECT_ID} PROPERTIES  VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/$(Configuration)")
endif()

if( DEFINED IOS_PLATFORM )
    # iOS requires special packaging, so we have to treat this target separately
    set_target_properties(${PROJECT_ID} PROPERTIES MACOSX_BUNDLE YES)
    set_target_properties(${PROJECT_ID} PROPERTIES MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/iOS/Info.plist")
    target_sources(${PROJECT_ID} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/iOS/LaunchScreen.storyboard)
    target_sources(${PROJECT_ID} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/cat.jpg)
    target_sources(${PROJECT_ID} PRIVATE iOS/libcxx_tmp_stubs.cpp)
    set(SPRITES_RESOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/iOS/LaunchScreen.storyboard"
        "${CMAKE_CURRENT_SOURCE_DIR}/cat.jpg"
    )
    set_target_properties(${PROJECT_ID} PROPERTIES RESOURCE "${SPRITES_RESOURCES}")
    set_target_properties(${PROJECT_ID} PROPERTIES XCODE_ATTRIBUTE_TARGETED_DEVICE_FAMILY "1,2")
endif()
