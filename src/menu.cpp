#include <iostream>
#include <string>


#include "menu.h"
#include "consoleapperance.h"
#include "banners.h"
#include "users.h"

#ifdef _WIN32
#define CLEAR system("cls")
#define GETCH _getch()
#define PAUSE system("pause")
#include <conio.h>
#elif _WIN64
#define CLEAR system("cls")
#define GETCH _getch()
#define PAUSE system("pause")
#include <conio.h>
#else
#define CLEAR std::system("clear")
#define GETCH getch()
#define PAUSE std::cin.get();
#include <ncurses.h>
#endif



void Menu::deafult() {
        CLEAR;
        displayHeader();
        if (currentUser != nullptr && currentUser->isAuthenticated)
        {
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
        if (currentUser != nullptr && currentUser->isAuthenticated)
        {
            if (currentUser->isAdmin)
            {
                this->options = {"Offer", "Edit Offer", "Rental History", "Financial Balances", "Log Out"};
            }
            else
            {
                this->options = {"Offer", "Rental Status", "Rental History", "Log Out"};
            }
        }
        else
        {
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
     currentUser = new User(login);
     currentUser->saveToDb(password);
     currentUser->authenticateUser(password);
     updateMenuOptions();
     signIn();
}

void Menu::loginChecker(std::string login){
    if(login.empty()){
        ConsoleAppearance::SetColor(4, 0);
        std::cout << "\n" << "Your login CANNOT be empty" << std::endl;
        ConsoleAppearance::SetColor(7, 0);
        PAUSE;        
        signUp();
    }
    for (char c : login) {
        if (!isalnum(c)) {
            ConsoleAppearance::SetColor(4, 0);
            std::cout << "\n" << "Your login contains characters that are not allowed" << std::endl;
            ConsoleAppearance::SetColor(7, 0);
            PAUSE;            
            signUp();
        }
    }
    if(login.length()<3 || login.length()>20){
        ConsoleAppearance::SetColor(4, 0);
        std::cout << "\n" << "Your login must be between 3 and 20 characters" << std::endl;
        ConsoleAppearance::SetColor(7, 0);
        PAUSE;        
        signUp();
    }
    if(userExists(login)){
        ConsoleAppearance::SetColor(4, 0);
        std::cout << "\n" << "The user arleady exist" << std::endl;
        ConsoleAppearance::SetColor(7, 0);
        PAUSE;        
        signUp();
    }
}

void Menu::passwordChecker(std::string password, std::string confPassword){

        if(password.empty()){
            ConsoleAppearance::SetColor(4, 0);
            std::cout << "\n" << "Your password CANNOT be empty" << std::endl;
            ConsoleAppearance::SetColor(7, 0);
            PAUSE;            
            signUp();
        }else if(password!=confPassword){
            ConsoleAppearance::SetColor(4, 0);
            std::cout << "\n" << "Passwords do not match" << std::endl;
            ConsoleAppearance::SetColor(7, 0);
            PAUSE;            
            signUp();
        }

        for (char c : password) {
            if (c == ' ') {
                ConsoleAppearance::SetColor(4, 0);
                std::cout << "\n" << "Your password contains characters that are not allowed" << std::endl;
                ConsoleAppearance::SetColor(7, 0);
                PAUSE;                
                signUp();
            }
        }

        if(password.length()<8){
            ConsoleAppearance::SetColor(4, 0);
            std::cout << "\n" << "Your password must be at least 8 characters" << std::endl;
            ConsoleAppearance::SetColor(7, 0);
            PAUSE;            
            signUp();
        }else{
            
            std::cout << "\n" << "User successfully created" << std::endl;
            PAUSE;            
        }
}

void Menu::signIn(){
    CLEAR;
    std::string login;
    std::string password;
    displaySignInBanner();
    std::cout << "Login: ";
    std::getline (std::cin, login);

    if (!userExists(login)){
        std::cout << "\n"<< "User with this login doesn't exist" << std::endl;
        PAUSE;
        this->signIn();
        return;
    } 

    std::cout << "Password: ";
    std::getline (std::cin, password);

    currentUser = new User(login);

    if (currentUser->authenticateUser(password)) {
        updateMenuOptions();
        std::cout << "\n"<< "You have successfully signed in" << "\n"<< std::endl;
    } else {
        std::cout << "\n"<< "Invalid login or password" << std::endl;
        delete currentUser;
    }
    
    PAUSE;
    navigation();
}

void Menu::greetingUser(){
    std::string user = currentUser->login;
    std::string greetings = "Hello " + user + "!";
    int padding = (34-greetings.length())/2;
    ConsoleAppearance::SetColor(9, 0);
    std::cout << std::string(padding, ' ');
    std::cout << greetings <<  std::endl;
}

#ifdef _WIN32
void Menu::navigation() {
        while (true) {
            deafult();

            int key = GETCH;

            if (key == 224) { // Special key
                key = GETCH;

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
                    delete currentUser;
                    currentUser = nullptr;
                    updateMenuOptions();
                } else {
                    std::cout << "You have selected: " << options[selectedOption] << std::endl;
                    PAUSE;                
                    }
            }
        }
    }
#elif _WIN64
void Menu::navigation() {
        while (true) {
            deafult();

            int key = GETCH;

            if (key == 224) { // Special key
                key = GETCH;

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
                    delete currentUser;
                    currentUser = nullptr;
                    updateMenuOptions();
                } else {
                    std::cout << "You have selected: " << options[selectedOption] << std::endl;
                    PAUSE;
                }
            }
        }
    }

#else
void Menu::navigation() {
    while (true) {
        deafult();

        // Initialize curses
        initscr();
        noecho();
        cbreak();
        keypad(stdscr, TRUE); // Enable special keys

        int key = GETCH;

        endwin(); // End curses mode

        if (key == KEY_UP) {
            selectedOption = (selectedOption - 1 + numOptions) % numOptions;
        } else if (key == KEY_DOWN) {
            selectedOption = (selectedOption + 1) % numOptions;
        } else if (key == 10) { // Enter key
            if (options[selectedOption] == "Exit") {
                std::cout << "Thank you for visiting! Goodbye\n";
                break;
            } else if (options[selectedOption] == "Sign Up") {
                signUp();
            } else if (options[selectedOption] == "Sign In") {
                signIn();
            } else if (options[selectedOption] == "Log Out") {
                delete currentUser;
                currentUser = nullptr;
                updateMenuOptions();
            } else {
                std::cout << "You have selected: " << options[selectedOption] << std::endl;
                PAUSE;
            }
        }
    }
}

#endif