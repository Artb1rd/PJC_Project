cmake_minimum_required(VERSION 3.21)
project(Pokemonv0_5)

set(CMAKE_CXX_STANDARD 20)

add_executable(Pokemonv0_5 main.cpp Pokemon.cpp Pokemon.h Player.cpp Player.h Engine.cpp Engine.h Game.cpp Game.h)
