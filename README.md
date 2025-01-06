# movieRental

## Description:
The C++ Movie Rental Application is a console-based program designed to streamline the process of renting movies for users. Built using object-oriented programming principles, the application provides a practical implementation of core C++ features, such as classes, file handling, inheritance, and data structures.

## Installation:
1. Install latest version of [CMake](https://cmake.org/download/)
    - On [Windows](https://www.microsoft.com/en-us/windows/?r=1): Head to [CMake website](https://cmake.org/download/) and install it from there
    - On [Arch](https://archlinux.org/): Run `pacman -Syu cmake`
    - On [Debian](https://www.debian.org/index.pl.html): Run `sudo apt update && sudo apt upgrade` and `sudo apt install cmake` 
    - On [Fedora](https://fedoraproject.org/): Run `sudo dnf install cmake`

2. Download this project:
    ```shell
    git clone https://github.com/Wiktor-Sikora/movieRental.git
    cd movieRental
    ```

3. Build project files and run executable:
    - On **Windows**:
    ```shell
    cmake -S . -B build
    cmake --build build --config release
    .\build\Release\movieRentalApp.exe
    ```

    - On **Linux**:
    ```shell
    cmake -S . -B build
    cmake --build build
    ./build/movieRentalApp
    ```

## License
This project is licensed under the MIT License, allowing anyone to freely use, modify, distribute, or incorporate the code into their own projects. The license ensures minimal restrictions, requiring only that the original copyright and license notice are included in any distributed copies or substantial portions of the software.
