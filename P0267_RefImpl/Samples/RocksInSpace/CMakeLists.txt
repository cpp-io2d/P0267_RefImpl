cmake_minimum_required(VERSION 3.0.0)
project(io2d CXX)

set(CMAKE_CXX_STANDARD 17)

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
elseif( ${CMAKE_SYSTEM_NAME} MATCHES "Linux" )
	list(APPEND ROCKS_IN_SPACE_SRC
		LinuxMain.cpp
	)
elseif( ${CMAKE_SYSTEM_NAME} MATCHES "Emscripten" )
	list(APPEND ROCKS_IN_SPACE_SRC
		SDL2Main.cpp
	)
else()
	message( "RocksInSpace doesn't have a frontend for this platform (${CMAKE_SYSTEM_NAME}), thus skipping." )
	return()
endif()

add_executable(rocks_in_space ${EXECUTABLE_FLAGS} ${ROCKS_IN_SPACE_SRC})

target_link_libraries(rocks_in_space io2d)

if( ${CMAKE_SYSTEM_NAME} MATCHES "Darwin" )
	target_link_libraries(rocks_in_space "-framework CoreFoundation")
	target_link_libraries(rocks_in_space "-framework CoreGraphics")
endif()

install(TARGETS rocks_in_space
	RUNTIME DESTINATION ${CMAKE_BINARY_DIR}/samples
)
