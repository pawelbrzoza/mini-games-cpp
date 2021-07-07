cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_VERSION 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) # to ensure the -std=c++17 flag will be passed to the compiler

project(Arkanoid)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "-g")
# set(CMAKE_CXX_FLAGS_RELEASE "-O3")

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

add_executable(Arkanoid src/Game.cpp
                        src/GameMenu.cpp
                        src/GameSettings.cpp
                        src/Level.cpp
                        src/LevelCurrent.cpp
                        main.cpp)

target_include_directories(Arkanoid PUBLIC include include/items)

target_link_libraries(Arkanoid sfml-network sfml-audio sfml-graphics sfml-window sfml-system)

