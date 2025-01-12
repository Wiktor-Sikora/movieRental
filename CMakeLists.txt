# Minimum required CMake version
cmake_minimum_required(VERSION 3.30)

# Compiler
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

# Project name and version
project(movieRental VERSION 0.1.0)

# C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Platform-specific configurations
if(WIN32)
    message(STATUS "Configuring for Windows")
elseif(UNIX)
    message(STATUS "Configuring for Linux")
    find_package(Curses REQUIRED)
    include_directories(${CURSES_INCLUDE_DIR})
endif()

# executable target
add_executable(movieRentalApp 
    src/main.cpp 
    src/utils.cpp 
    src/db.cpp src/db.h 
    src/movies.cpp src/movies.h
    src/sqlite3.c src/sqlite3.h
    src/menu.cpp src/menu.h
    src/banners.h
    src/consoleapperance.h
    src/users.cpp src/users.h
)

if(UNIX)
    target_link_libraries(movieRentalApp ${CURSES_LIBRARIES})
endif()
