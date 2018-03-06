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
endif()

add_executable(rocks_in_space ${EXECUTABLE_FLAGS} ${ROCKS_IN_SPACE_SRC})

target_link_libraries(rocks_in_space io2d)

install(TARGETS rocks_in_space
	RUNTIME DESTINATION ${CMAKE_BINARY_DIR}/samples
)
