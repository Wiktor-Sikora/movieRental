#include <iostream>
#include <string>


#include "menu.h"
#include "consoleapperance.h"
#include "banners.h"
#include "users.h"
#include "offer.h"
#include "finance.h"
#include "renting.h"

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
        skipDefaultView = false;
        skipEditOfferView = true;
        skipManageUsersView = true;
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
    delete menuOptions;
    if (currentUser != nullptr && currentUser->isAuthenticated) {
        if (currentUser->isAdmin) {
            menuOptions = new AdminMenuOptions();
        }else {
            menuOptions = new UserMenuOptions();
        }
    }else {
        menuOptions = new GuestMenuOptions();
    }

    options = menuOptions->getOptions();
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
     if(login.empty()){return;}
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
        deafult();
        return;
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

    if(login.empty()){
        ConsoleAppearance::SetColor(4, 0);
        std::cout << "\n" << "Your login CANNOT be empty" << std::endl;
        ConsoleAppearance::SetColor(7, 0);
        PAUSE;
        deafult();
        return;
        }

    if (!userExists(login)){
        ConsoleAppearance::SetColor(4, 0);
        std::cout << "\n"<< "User with this login doesn't exist" << std::endl;
        ConsoleAppearance::SetColor(7, 0);
        PAUSE;
        this->signIn();
        return;
    }

    if(isBlocked(login)){
        ConsoleAppearance::SetColor(4, 0);
        std::cout << "\n"<< "This user account is blocked" << std::endl;
        ConsoleAppearance::SetColor(7, 0);
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
        ConsoleAppearance::SetColor(4, 0);
        std::cout << "\n"<< "Invalid login or password" << std::endl;
        ConsoleAppearance::SetColor(7, 0);
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

void Menu::movieMenu(User &currentUser) {
    movieOffer.displayMovies(currentUser);
}

void Menu::add() {
    Offer offer;
    offer.addMovie();
}

void Menu::editOffer(){
    CLEAR;
    skipDefaultView = true;
    skipEditOfferView = false;
    skipManageUsersView = true;
    EditOfferMenuOptions opt;
    options = opt.getOptions();
    numOptions = options.size();

    displayEditOfferBanner();

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

void Menu::manageUsersMenu(){
    CLEAR;
    skipDefaultView = true;
    skipEditOfferView = true;
    skipManageUsersView = false;
    ManageUsersMenuOptions opt;
    options = opt.getOptions();
    numOptions = options.size();

    displayManageUsersBanner();

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

void Menu::blockUser(){
    CLEAR;
    displayBlockUserBanner();
    std::string username;
    std::cout << "Enter the login of the user you want to block:\n";
    std::getline (std::cin, username);
    
    if(username.empty()){
        ConsoleAppearance::SetColor(4, 0);
        std::cout << "\n" << "This field cannot be empty." << std::endl;
        ConsoleAppearance::SetColor(7, 0);
        PAUSE;
        deafult();
        return;
    }

    if(username == currentUser->login){
        ConsoleAppearance::SetColor(4, 0);
        std::cout << "\n" << "You can't." << std::endl;
        ConsoleAppearance::SetColor(7, 0);
        PAUSE;
        return;
    }

    if(!userExists(username)){
        ConsoleAppearance::SetColor(4, 0);
        std::cout << "\n" << "This username does not exist." << std::endl;
        ConsoleAppearance::SetColor(7, 0);
        PAUSE;        
        blockUser();
    }
    User mUser = getUser(username);
    if(!isBlocked(username)){
        mUser.isBlocked = true;
        mUser.saveToDb("");
        std::cout << "User successfully blocked." << std::endl;
        PAUSE;
    }else{
        ConsoleAppearance::SetColor(4, 0);
        std::cout << "\nThis user is arleady blocked.\n";
        ConsoleAppearance::SetColor(7, 0);
        PAUSE;
        blockUser();
    }
}

void Menu::unblockUser(){
    CLEAR;
    displayBlockUserBanner();
    std::string username;
    std::cout << "Enter the login of the user you want to unblock:\n";
    std::getline (std::cin, username);
    
    if(username.empty()){
        ConsoleAppearance::SetColor(4, 0);
        std::cout << "\n" << "This field cannot be empty." << std::endl;
        ConsoleAppearance::SetColor(7, 0);
        PAUSE;
        deafult();
        return;
    }
    
    if(username == currentUser->login){
        ConsoleAppearance::SetColor(4, 0);
        std::cout << "\n" << "You can't." << std::endl;
        ConsoleAppearance::SetColor(7, 0);
        PAUSE;
        return;
    }

    if(!userExists(username)){
        ConsoleAppearance::SetColor(4, 0);
        std::cout << "\n" << "This username does not exist." << std::endl;
        ConsoleAppearance::SetColor(7, 0);
        PAUSE;        
        unblockUser();
    }
    User mUser = getUser(username);
    if(isBlocked(username)){
        mUser.isBlocked = false;
        mUser.saveToDb("");
        std::cout << "User successfully unblocked." << std::endl;
        PAUSE;
    }else{
        ConsoleAppearance::SetColor(4, 0);
        std::cout << "\nThis user is arleady unblocked.\n";
        ConsoleAppearance::SetColor(7, 0);
        PAUSE;
        unblockUser();
    }
}

void Menu::finances(){
    CLEAR;
    std::cout << "Profit:\t\t" << getProfit() << "$\n";
    std::cout << "Expenses:\t" << getExpenses() << "$\n";
    std::cout << "Balance:\t" << getBalance() << "$\n";
    PAUSE;
}

#ifdef _WIN32
void Menu::navigation() {
        while (true) {

           if (!skipDefaultView) {
            deafult();
            }else if (!skipEditOfferView){
                editOffer();
            }else if (!skipManageUsersView){
                manageUsersMenu();
            }
            

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
                } else if (key == 27) { //Esc
                    break;
                }else if (key == 13) { // Enter
                if (options[selectedOption] == "Exit") {
                    std::cout << "Thank you for visiting! Goodbye\n";
                    break;
                }else{
                    executeOption();
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
                } else if (key == 27) { //Esc
                    break;
                }else if (key == 13) { // Enter
                if (options[selectedOption] == "Exit") {
                    std::cout << "Thank you for visiting! Goodbye\n";
                    break;
                }else{
                    executeOption();
                }
                
            }
        }
    }

#else
void Menu::navigation() {
    while (true) {
        deafult();
        ESCDELAY = 50;
        // Initialize curses
        initscr();
        noecho();
        cbreak();
        keypad(stdscr, TRUE); // Enable special keys

        int key = GETCH;

        if (key == 27) {

            nodelay(stdscr, TRUE);
            int nextChar = getch();
            nodelay(stdscr, FALSE);

            if (nextChar == ERR) {
                endwin();
                return;
            } else {
                ungetch(nextChar);
            }
        }

        endwin();

        if (key == KEY_UP) {
            selectedOption = (selectedOption - 1 + numOptions) % numOptions;
        } else if (key == KEY_DOWN) {
            selectedOption = (selectedOption + 1) % numOptions;
        } 
        else if (key == 10) { // Enter key
            if (options[selectedOption] == "Exit") {
                std::cout << "Thank you for visiting! Goodbye\n";
                break;
            }else{
                executeOption();
            }
        }
    }
}

#endif


void Menu::executeOption(){
    if(options[selectedOption] == "Offer"){
            movieOffer.isDisplay = true;
            movieMenu(*currentUser);
        }else if(options[selectedOption] == "Edit Offer"){
            editOffer();
        }else if(options[selectedOption] == "Add Movie"){
            add();
        }else if(options[selectedOption] == "Delete Movie"){
            movieOffer.isDisplay = false;
            movieOffer.displayMovies(*currentUser);
        }else if(options[selectedOption] == "Manage Users"){
            manageUsersMenu();
        }else if(options[selectedOption] == "Block User"){
            blockUser();
        }else if(options[selectedOption] == "Unblock User"){
            unblockUser();
        }else if(options[selectedOption] == "Rental Status"){
            movieRenting.displayRentedMovies(*currentUser);
        }else if(options[selectedOption] == "Rental History"){
            movieRenting.displayRentalHistory(*currentUser);
        }else if(options[selectedOption] == "Financial Balances"){
            finances();
        }else if(options[selectedOption] == "Sign Up"){
            signUp();
        }else if(options[selectedOption] == "Sign In"){
            signIn();
        }else if(options[selectedOption] == "Return"){
            deafult();
            updateMenuOptions();
        }else if(options[selectedOption] == "Log Out"){
            delete currentUser;
            currentUser = nullptr;
            updateMenuOptions();
        } else {
            std::cout << "You have selected: " << options[selectedOption] << std::endl;
            PAUSE;                
        }
}