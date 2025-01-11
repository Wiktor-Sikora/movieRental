#ifndef MENU_H
#define MENU_H


#include <iostream>
#include <vector>

class Menu
{
private:
    std::vector<std::string> options;
    int numOptions;
    int selectedOption;
    bool isLoggedIn;
    bool isAdmin;
    

public:
    Menu(const std::string optionsArray[], int numberOfOptions) {
        isLoggedIn = false;
        isAdmin = false;
        numOptions = numberOfOptions;
        options.assign(optionsArray, optionsArray + numberOfOptions);
        selectedOption = 0;
    }

    void deafult();
    void updateMenuOptions();
    void signUp();
    void loginChecker(std::string login);
    void passwordChecker(std::string password, std::string confPassword);
    void signIn();
    void greetingUser();
    void navigation();
};

#endif