#ifndef MENU_H
#define MENU_H


#include <iostream>
#include <vector>
#include "users.h"
#include "movies.h"
#include "offer.h"
#include "renting.h"

class MenuOptions;

class Menu
{
private:
    std::vector<std::string> options;
    User* currentUser;
    User* mUser;
    int numOptions;
    int selectedOption;
    MenuOptions* menuOptions;
    Offer movieOffer;
    Renting movieRenting;
    bool skipDefaultView = false;
    bool skipEditOfferView = true;
    bool skipManageUsersView = true;

public:

    Menu(const std::string optionsArray[], int numberOfOptions): currentUser(nullptr), mUser(nullptr), numOptions(0), selectedOption(0), menuOptions(nullptr) {
    options = {"Offer", "Sign Up", "Sign In", "Exit"}; 
    }

    ~Menu(){};

    void deafult();
    void updateMenuOptions();
    void signUp();
    void loginChecker(std::string login);
    void passwordChecker(std::string password, std::string confPassword);
    void signIn();
    void greetingUser();
    void displayMovie();
    void movieMenu(User &currentUser);
    void add();
    void mDelete(Movie& movie, User &currentUser);
    void editOffer();
    void navigation();
    void executeOption();
    void manageUsersMenu();
    void blockUser();
    void unblockUser();
    void finances();
};

class MenuOptions {
public:
    virtual std::vector<std::string> getOptions() const = 0;
    virtual ~MenuOptions() = default;
};

class AdminMenuOptions : public MenuOptions {
public:
    std::vector<std::string> getOptions() const override {
        return {"Offer", "Edit Offer", "Manage Users", "Rental History", "Financial Balances", "Log Out"};
    }
};

class UserMenuOptions : public MenuOptions {
public:
    std::vector<std::string> getOptions() const override {
        return {"Offer", "Rental Status", "Rental History", "Log Out"};
    }
};

class GuestMenuOptions : public MenuOptions {
public:
    std::vector<std::string> getOptions() const override {
        return {"Offer", "Sign Up", "Sign In", "Exit"};
    }
};

class EditOfferMenuOptions : public MenuOptions {
public:
    std::vector<std::string> getOptions() const override {
        return {"Add Movie", "Delete Movie", "Return"};
    }
};

class ManageUsersMenuOptions : public MenuOptions {
public:
    std::vector<std::string> getOptions() const override {
        return {"Block User", "Unblock User", "Return"};
    }
};

#endif