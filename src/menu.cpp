#include <iostream>
#include <string>
#include <conio.h>

#include "menu.h"
#include "consoleapperance.h"
#include "banners.h"

#ifdef _WIN32
#define CLEAR system("cls")
#elif _WIN64
#define CLEAR system("cls")
#else
#define CLEAR std::system("clear")
#endif



void Menu::deafult() {
        CLEAR;
        displayHeader();
        if(isLoggedIn){
            greetingUser();
        }
        for (int i = 0; i < numOptions; i++) {
            ConsoleAppearance::centerText(options[i]);
            if (i == selectedOption) {
                ConsoleAppearance::SetColor(0, 7);
                std::cout << " " << options[i] << " " << std::endl;
                ConsoleAppearance::SetColor(7, 0);
            } else {
                ConsoleAppearance::SetColor(7, 0);
                std::cout << " " << options[i] << " " << std::endl;
            }
        }
    }

void Menu::updateMenuOptions() {
        if (isLoggedIn) {
            if (isAdmin) {
                this->options = {"Offer", "Edit Offer", "Rental History", "Financial Balances", "Log Out"};
            } else {
                this->options = {"Offer", "Rental Status", "Rental History", "Log Out"};
            }
        } else {
            this->options = {"Offer", "Sign Up", "Sign In", "Exit"};
        }
        numOptions = options.size();
        selectedOption = 0;
    }

void Menu::signUp(){
     CLEAR;
     std::string login;
     std::string password;
     std::string confPassword;
     displaySignUpBanner();
     std::cout << "\n";
     std::cout << "Login: ";
     std::getline (std::cin, login);
     loginChecker(login);
     std::cout << "Password: ";
     std::getline (std::cin, password); 
     std::cout << "Confirm password: ";
     std::getline (std::cin, confPassword);
     passwordChecker(password, confPassword);
}

void Menu::loginChecker(std::string login){
    if(login.empty()){
        ConsoleAppearance::SetColor(4, 0);
        std::cout << "\n" << "Your login CANNOT be empty" << std::endl;
        ConsoleAppearance::SetColor(7, 0);
        system("pause");
        signUp();
    }
    for (char c : login) {
        if (!isalnum(c)) {
            ConsoleAppearance::SetColor(4, 0);
            std::cout << "\n" << "Your login contains characters that are not allowed" << std::endl;
            ConsoleAppearance::SetColor(7, 0);
            system("pause");
            signUp();
        }
    }
    if(login.length()<3 || login.length()>20){
        ConsoleAppearance::SetColor(4, 0);
        std::cout << "\n" << "Your login must be between 3 and 20 characters" << std::endl;
        ConsoleAppearance::SetColor(7, 0);
        system("pause");
        signUp();
    }
}

void Menu::passwordChecker(std::string password, std::string confPassword){

        if(password.empty()){
            ConsoleAppearance::SetColor(4, 0);
            std::cout << "\n" << "Your password CANNOT be empty" << std::endl;
            ConsoleAppearance::SetColor(7, 0);
            system("pause");
            signUp();
        }else if(password!=confPassword){
            ConsoleAppearance::SetColor(4, 0);
            std::cout << "\n" << "Passwords do not match" << std::endl;
            ConsoleAppearance::SetColor(7, 0);
            system("pause");
            signUp();
        }

        for (char c : password) {
            if (c == ' ') {
                ConsoleAppearance::SetColor(4, 0);
                std::cout << "\n" << "Your password contains characters that are not allowed" << std::endl;
                ConsoleAppearance::SetColor(7, 0);
                system("pause");
                signUp();
            }
        }

        if(password.length()<8){
            ConsoleAppearance::SetColor(4, 0);
            std::cout << "\n" << "Your password must be at least 8 characters" << std::endl;
            ConsoleAppearance::SetColor(7, 0);
            system("pause");
            signUp();
        }else{
            std::cout << "\n" << "User successfully created" << std::endl;
            system("pause");
            signIn();
        }
}

void Menu::signIn(){
    CLEAR;
    std::string login;
    std::string password;
    displaySignInBanner();
    std::cout << "Login: ";
    std::getline (std::cin, login);
    std::cout << "Password: ";
    std::getline (std::cin, password); 
    std::cout << "\n" << "You have successfully signed in" << "\n" << std::endl;
    isLoggedIn = true;
    updateMenuOptions();
    system("pause");
    navigation();
}

void Menu::greetingUser(){
    std::string user = "user";
    std::string greetings = "Hello " + user + "!";
    int padding = (34-greetings.length())/2;
    ConsoleAppearance::SetColor(9, 0);
    std::cout << std::string(padding, ' ');
    std::cout << greetings <<  std::endl;
}

void Menu::navigation() {
        while (true) {
            deafult();

            int key = _getch();

            if (key == 224) { // Special key
                key = _getch();
                switch (key) {
                case 72: // Up arrow
                    selectedOption = (selectedOption - 1 + numOptions) % numOptions;
                    break;
                case 80: // Down arrow
                    selectedOption = (selectedOption + 1) % numOptions;
                    break;
                }
            } else if (key == 13) { // Enter
                if (options[selectedOption] == "Exit") {
                    std::cout << "Thank you for visiting! Goodbye\n";
                    break;
                }
                else if(options[selectedOption] == "Sign Up"){
                    signUp();
                }else if(options[selectedOption] == "Sign In"){
                    signIn();
                }else if(options[selectedOption] == "Log Out"){
                    isLoggedIn = false;
                    isAdmin = false;
                    updateMenuOptions();
                } else {
                    std::cout << "You have selected: " << options[selectedOption] << std::endl;
                    system("pause");
                }
            }
        }
    }