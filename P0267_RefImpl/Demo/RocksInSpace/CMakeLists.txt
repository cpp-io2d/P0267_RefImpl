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
	MacMain.cpp
)

add_executable(rocks_in_space ${ROCKS_IN_SPACE_SRC})

target_link_libraries(rocks_in_space io2dlib)
