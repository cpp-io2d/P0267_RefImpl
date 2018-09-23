cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 17)

if(EMSCRIPTEN)
	message("Skipping the sprites example due to lack of Emscripten support")
	return()
endif()

project(sprites)
add_executable(sprites main.cpp)
target_link_libraries(sprites io2d)

add_custom_command( TARGET sprites POST_BUILD
 COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/cat.jpg" "$<TARGET_FILE_DIR:sprites>/cat.jpg"
)

if(MSVC)
	set_target_properties(sprites PROPERTIES  VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/$(Configuration)")
endif()

if( DEFINED IOS_PLATFORM )
    # iOS requires special packaging, so we have to treat this target separately
    set_target_properties(sprites PROPERTIES MACOSX_BUNDLE YES)
    set_target_properties(sprites PROPERTIES MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/iOS/Info.plist")
    target_sources(sprites PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/iOS/LaunchScreen.storyboard)
    target_sources(sprites PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/cat.jpg)
    target_sources(sprites PRIVATE iOS/libcxx_tmp_stubs.cpp)
    set(SPRITES_RESOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/iOS/LaunchScreen.storyboard"
        "${CMAKE_CURRENT_SOURCE_DIR}/cat.jpg"
    )
    set_target_properties(sprites PROPERTIES RESOURCE "${SPRITES_RESOURCES}")
    set_target_properties(sprites PROPERTIES XCODE_ATTRIBUTE_TARGETED_DEVICE_FAMILY "1,2")
endif()
