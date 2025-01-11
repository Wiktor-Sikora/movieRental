#ifndef BANNERS_H
#define BANNERS_H
#include <iostream>


void displayHeader() {
    std::cout << "##################################" << std::endl;
    std::cout << "#          MOVIE RENTAL          #" << std::endl;
    std::cout << "##################################" << std::endl;
}

void displaySignUpBanner(){
    std::cout << "**********************************" << std::endl;
    std::cout << "*             SIGN UP            *" << std::endl;
    std::cout << "**********************************" << std::endl;
}

void displaySignInBanner(){
    std::cout << "**********************************" << std::endl;
    std::cout << "*             SIGN IN            *" << std::endl;
    std::cout << "**********************************" << std::endl;
}

#endif