# Windows build and installation

0. Download and install gcc gdb, (https://www.msys2.org/)
1. Find SFML lib for your platform using: pacman -Ss sfml command and install: pacman -S mingw-w64-x86_64-sfml
2. In the main dir execute: mkdir build && cd build && Xcopy /E /I ..\data data
3. Copy SFML libs into build dir (.dll)
4. In the build dir execute:
   cmake .. -G"MinGW Makefiles"
   cmake --build .
   Arkanoid.exe


# Linux build and installation

1. Install SFML libs: sudo apt-get install libsfml-dev
2. In the main dir execute: mkdir build && cd build && cp -R ../data data
3. In the build dir execute:
   cmake ..
   make
   ./Arkanoid
