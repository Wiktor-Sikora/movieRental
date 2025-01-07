# Minimum required CMake version
cmake_minimum_required(VERSION 3.30)

# Project name and version
project(movieRental VERSION 1.0)

# C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# executable target
add_executable(movieRentalApp 
    src/main.cpp 
    src/utils.cpp 
    src/db.cpp src/db.h 
    src/sqlite3.c 
    src/movies.cpp
)

# Platform-specific configurations
if(WIN32)
    message(STATUS "Configuring for Windows")
elseif(UNIX)
    message(STATUS "Configuring for Linux/Unix")
endif()

# install rules
# install(TARGETS MyApp DESTINATION bin)