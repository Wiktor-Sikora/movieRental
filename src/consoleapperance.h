#ifndef CONSOLE_APEERANCE_H
#define CONSOLE_APEERANCE_H
#include <Windows.h>

class ConsoleAppearance {
public:
    static void SetColor(int textColor, int bgColor) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, (bgColor << 4) | textColor);
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