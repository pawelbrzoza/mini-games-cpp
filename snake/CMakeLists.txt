cmake_minimum_required(VERSION 3.10)

project(Snake)

add_executable(Snake main.cpp)

target_include_directories(Snake PUBLIC Game.hpp Snake.hpp Board.hpp Common.hpp)