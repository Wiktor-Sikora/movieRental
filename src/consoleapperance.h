#ifndef CONSOLE_APEERANCE_H
#define CONSOLE_APEERANCE_H

#ifdef _WIN32
#include <Windows.h>
#elif _WIN64
#include <Windows.h>
#else
#include <stdio.h>
#endif

class ConsoleAppearance {
public:
    
    enum Color{
        BLACK = 0, RED = 4, WHITE = 7
    };

    static void SetColor(int textColor, int bgColor) {
#ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, (bgColor << 4) | textColor);
#elif _WIN64
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, (bgColor << 4) | textColor);
#else
        std::cout << "\033[" << (30 + textColor) << ";" << (40 + bgColor) << "m";
#endif
    }
    
    static void centerText(const std::string& text, int width = 32) {
        int totalPadding = width - text.length();
        int leftPadding = totalPadding / 2;
        std::cout << std::string(leftPadding, ' ');
    }
};

#endif

/*
gray - SetColor(0, 0)
blue - SetColor(1, 0)
green - SetColor(2, 0)
cyan - SetColor(3, 0)
red - SetColor(4, 0)
magenta - SetColor(5, 0)
yellow - SetColor(6, 0)
white - SetColor(7, 0)
light_gray - SetColor(8, 0)
bright_blue - SetColor(9, 0)
bright_green - SetColor(10, 0)
bright_cyan - SetColor(11, 0)
bright_red - SetColor(12, 0)
pink - SetColor(13, 0)
bright_yellow - SetColor(14, 0)
jasny_fijoł - SetColor(15, 0)
*/