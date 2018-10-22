cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 17)

# Use the CMakeLists.txt's parent-directory-name for the project's id/name
get_filename_component(PROJECT_ID ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" PROJECT_ID ${PROJECT_ID})
project(${PROJECT_ID})

set(ROCKS_IN_SPACE_SRC 
	Asteroid.h
	Asteroid.cpp
	Constants.h
	Game.h
	Game.cpp
	Input.h
	Input.cpp
	Maths.h
	Maths.cpp
	Physics.h
	Physics.cpp
	Ship.h
	Ship.cpp
	Types.h
)

if( ${CMAKE_SYSTEM_NAME} MATCHES "Darwin" )
	list(APPEND ROCKS_IN_SPACE_SRC
		MacMain.cpp
	)
elseif( ${CMAKE_SYSTEM_NAME} MATCHES "Windows" )
	list(APPEND ROCKS_IN_SPACE_SRC
		WinMain.cpp
		Win32Win.cpp
	)
	set(EXECUTABLE_FLAGS WIN32)
elseif( ${IO2D_DEFAULT} MATCHES "CAIRO_SDL2" )
	list(APPEND ROCKS_IN_SPACE_SRC
		SDL2Main.cpp
	)
elseif( ${CMAKE_SYSTEM_NAME} MATCHES "Linux" )
	list(APPEND ROCKS_IN_SPACE_SRC
		LinuxMain.cpp
	)
else()
	message( "RocksInSpace doesn't have a frontend for this platform (${CMAKE_SYSTEM_NAME}), thus skipping." )
	return()
endif()

add_executable(${PROJECT_ID} ${EXECUTABLE_FLAGS} ${ROCKS_IN_SPACE_SRC})

target_link_libraries(${PROJECT_ID} io2d)

if( ${CMAKE_SYSTEM_NAME} MATCHES "Darwin" )
	target_link_libraries(${PROJECT_ID} "-framework CoreFoundation")
	target_link_libraries(${PROJECT_ID} "-framework CoreGraphics")
endif()

install(TARGETS ${PROJECT_ID}
	RUNTIME DESTINATION ${CMAKE_BINARY_DIR}/samples
)
