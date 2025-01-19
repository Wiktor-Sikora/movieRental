#include <iostream>
#include <string>
#include <format>
#include <cctype>

#include "menu.h"
#include "consoleapperance.h"
#include "offer.h"
#include "movies.h"
#include "users.h"
#include "banners.h"
// #include "db.h"



#ifdef _WIN32
#define CLEAR system("cls")
#define GETCH _getch()
#define PAUSE system("pause")
#define SYSTEM system("chcp 65001 > nul");
#include <conio.h>
#elif _WIN64
#define CLEAR system("cls")
#define GETCH _getch()
#define PAUSE system("pause")
#define SYSTEM system("chcp 65001 > nul");
#include <conio.h>
#else
#define CLEAR std::system("clear")
#define GETCH getch()
#define PAUSE std::cin.get();
#define SYSTEM 0;
#include <ncurses.h>
#endif


void Offer::displayMovieDetails(Movie& movie, User &currentUser) {
    isDisplay = true;
    std::vector<std::string> options = {"Rent", "Return"};
    int selectedOption = 0;
    while(true){
        SYSTEM;
        CLEAR;
        std::cout << std::string(movie.name.length() + 14, '=') << std::endl;
        std::cout << "||" << std::string(5, ' ') << movie.name << std::string(5, ' ') << "||" << std::endl;
        std::cout << std::string(movie.name.length() + 14, '=') << std::endl;

        std::cout << "Release date: " << movie.released << "\n\n";
        std::cout << "Description\n" << movie.description << "\n\n";
        std::cout << "$" << movie.price << " | " << movie.stock << " in stock\n" << std::endl;

        for (int i = 0; i < options.size(); ++i) {
            if (i == selectedOption) {
                ConsoleAppearance::SetColor(0, 7);
                std::cout << " " << options[i] << " " << std::endl;
                ConsoleAppearance::SetColor(7, 0);
            } else {
                ConsoleAppearance::SetColor(7, 0);
                std::cout << " " << options[i] << std::endl;
            }
        }
#ifdef _WIN32
        int key = GETCH;

        if (key == 224) { 
            key = GETCH;
            if (key == 72) {
                selectedOption = (selectedOption - 1 + options.size()) % options.size();
            } else if (key == 80) {
                selectedOption = (selectedOption + 1) % options.size();
            }
        } else if (key == 13) {
            if (options[selectedOption] == "Rent") {
                if(&currentUser == nullptr){
                    ConsoleAppearance::SetColor(4, 0);
                    std::cout << "You must be logged in to do that" << std::endl;
                    ConsoleAppearance::SetColor(7, 0);
                    break;
                }
                if (movie.stock > 0 && currentUser.isAuthenticated && currentUser.isAdmin == 0) {
                    movie.rentMovie(currentUser.getId());
                    std::cout << "Your purchase was successful!" << std::endl;
                    break;
                } else if(movie.stock == 0) {
                    ConsoleAppearance::SetColor(4, 0);
                    std::cout << "Out of stock!" <<  std::endl;
                    ConsoleAppearance::SetColor(7, 0);
                    PAUSE;
                }else if(currentUser.isAdmin){
                    ConsoleAppearance::SetColor(4, 0);
                    std::cout << "Only a regular user can rent a movie." <<  std::endl;
                    ConsoleAppearance::SetColor(7, 0);
                    PAUSE;
                }
            } else if (options[selectedOption] == "Return") {
                break;
            }
        } else if (key == 27) {
            return;
        }
#elif _WIN64
        int key = GETCH;

        if (key == 224) { 
            key = GETCH;
            if (key == 72) {
                selectedOption = (selectedOption - 1 + options.size()) % options.size();
            } else if (key == 80) {
                selectedOption = (selectedOption + 1) % options.size();
            }
        } else if (key == 13) {
            if (options[selectedOption] == "Rent") {
                if(&currentUser == nullptr){
                    ConsoleAppearance::SetColor(4, 0);
                    std::cout << "You must be logged in to do that" << std::endl;
                    ConsoleAppearance::SetColor(7, 0);
                    break;
                }
                if (movie.stock > 0 && currentUser.isAuthenticated && currentUser.isAdmin == 0) {
                    movie.rentMovie(currentUser.getId());
                    std::cout << "Your purchase was successful!" << std::endl;
                    break;
                } else if(movie.stock == 0) {
                    ConsoleAppearance::SetColor(4, 0);
                    std::cout << "Out of stock!" <<  std::endl;
                    ConsoleAppearance::SetColor(7, 0);
                    PAUSE;
                }else if(currentUser.isAdmin){
                    ConsoleAppearance::SetColor(4, 0);
                    std::cout << "Only a regular user can rent a movie." <<  std::endl;
                    ConsoleAppearance::SetColor(7, 0);
                    PAUSE;
                }
            } else if (options[selectedOption] == "Return") {
                break;
            }
        } else if (key == 27) {
            return;
        }
#else
        initscr();
        noecho();
        cbreak();
        keypad(stdscr, TRUE);

        int key = GETCH;

        endwin();

            if (key == KEY_UP) {
                selectedOption = (selectedOption - 1 + options.size()) % options.size();
            } else if (key == KEY_DOWN) {
                selectedOption = (selectedOption + 1) % options.size();
            }
             else if (key == 10) {
                if (options[selectedOption] == "Rent") {
                    if(&currentUser == nullptr){
                    ConsoleAppearance::SetColor(4, 0);
                    std::cout << "You must be logged in to do that" << std::endl;
                    ConsoleAppearance::SetColor(7, 0);
                    break;
                }
                if (movie.stock > 0 && currentUser.isAuthenticated && currentUser.isAdmin == 0) {
                    movie.rentMovie(currentUser.getId());
                    std::cout << "Your purchase was successful!" << std::endl;
                    break;
                } else if(movie.stock == 0) {
                    ConsoleAppearance::SetColor(4, 0);
                    std::cout << "Out of stock!" <<  std::endl;
                    ConsoleAppearance::SetColor(7, 0);
                    PAUSE;
                }else if(currentUser.isAdmin){
                    ConsoleAppearance::SetColor(4, 0);
                    std::cout << "Only a regular user can rent a movie." <<  std::endl;
                    ConsoleAppearance::SetColor(7, 0);
                    PAUSE;
                }
            } else if (options[selectedOption] == "Return") {
                break;
            }
            } else if (key == "\027") {
                return;
            }
#endif
    }
    }

void Offer::displayMovies(User &currentUser) {
    SYSTEM;
    CLEAR;
    std::string movieTitle;
    std::cout << "Enter the movie title to search: ";
    std::getline(std::cin, movieTitle);


    MoviesQuerySet movies(movieTitle);
    if (movies.querySet.empty()) {
        ConsoleAppearance::SetColor(4, 0);
        std::cout << "\nNo movies found with the title" << std::endl;
        ConsoleAppearance::SetColor(7, 0);
        PAUSE;
        displayMovies(currentUser);
    }

    int maxSize;
    if(movies.querySet.size()>15){
        maxSize = 15;
    }else{
        maxSize = movies.querySet.size();
    }

    int selectedIndex = 0;
    while (true) {
        CLEAR;
        std::cout << "Select a movie using Up/Down arrows and press Enter:\n\n";
        for (int i = 0; i < maxSize; ++i) {
            if (i == selectedIndex) {
                ConsoleAppearance::SetColor(0, 7);
                std::cout << " " << movies.querySet[i].name << " (" << movies.querySet[i].released << ")" << " " << "\n";
            } else {
                ConsoleAppearance::SetColor(7, 0);
                std::cout<< movies.querySet[i].name << " (" << movies.querySet[i].released << ")\n";
            }
        }
        ConsoleAppearance::SetColor(7, 0);

#ifdef _WIN32
        int key = GETCH;
        if (key == 224) {
            key = GETCH;
            if (key == 72) {
                selectedIndex = (selectedIndex - 1 + maxSize) % maxSize;
            } else if (key == 80) {
                selectedIndex = (selectedIndex + 1) % maxSize;
            }
        } else if (key == 13) {
            if(isDisplay){
                displayMovieDetails(movies.querySet[selectedIndex], currentUser);
            }else{
                displayForDeletion(movies.querySet[selectedIndex], currentUser);
            }
            
            break;
        } else if (key == 27) { //Esc
            break;
        }
#elif _WIN64
    int key = GETCH;
        if (key == 224) {
            key = GETCH;
            if (key == 72) {
                selectedIndex = (selectedIndex - 1 + maxSize) % maxSize;
            } else if (key == 80) {
                selectedIndex = (selectedIndex + 1) % maxSize;
            }
        } else if (key == 13) {
            displayMovieDetails(movies.querySet[selectedIndex]);
            break;
        } else if (key == 27) { //Esc
            break;
        }
#else
        initscr();
        noecho();
        cbreak();
        keypad(stdscr, TRUE);

        int key = GETCH;

        endwin();

        if (key == KEY_UP) {
            selectedIndex = (selectedIndex - 1 + maxSize) % maxSize;
        } else if (key == KEY_DOWN) {
            selectedIndex = (selectedIndex + 1) % maxSize;
        } else if (key == 10) { 
            displayMovieDetails(movies.querySet[selectedIndex], currentUser);
            break;
        } else if (key == "\027") { 
            break;
        }
#endif
    }
    PAUSE;
}




void Offer::addMovie() {
    CLEAR;
    displayAddMovieBanner();
    
    std::string name, description;
    int released, stock;
    float price;

    std::cout << "Enter the movie name: ";
    std::getline(std::cin, name);

    std::cout << "Enter the movie description: ";
    std::getline(std::cin, description);

      
    while (true) {
        std::cout << "Enter the movie release year: ";
        std::cin >> released;

        if (std::cin.fail() || released < 1888 || released > 2025) {
            std::cin.clear();
            std::cin.ignore(1024, '\n');
            ConsoleAppearance::SetColor(4, 0);
            std::cout << "Invalid release year. Please try again.\n";
            ConsoleAppearance::SetColor(7, 0);
        } else {
            break;
        }
    }

    while (true) {
        std::cout << "Enter the movie price: ";
        std::cin >> price;

        if (std::cin.fail() || price < 0) {
            std::cin.clear();
            std::cin.ignore(1024, '\n');
            ConsoleAppearance::SetColor(4, 0);
            std::cout << "Invalid price. Please try again.\n";
            ConsoleAppearance::SetColor(7, 0);
        } else {
            break;
        }
    }

    while (true) {
        std::cout << "Enter the movie stock quantity: ";
        std::cin >> stock;

        if (std::cin.fail() || stock < 0) {
            std::cin.clear();
            std::cin.ignore(1024, '\n');
            ConsoleAppearance::SetColor(4, 0);
            std::cout << "Invalid stock. Please try again.\n";
            ConsoleAppearance::SetColor(7, 0);
        } else {
            break;
        }
    }
    

    Movie newMovie(name, description, released, price, stock, -1);
    newMovie.saveToDb();

    std::cout << "Movie added successfully!" << std::endl;
    PAUSE;
    return;
}

void Offer::displayForDeletion(Movie& movie, User &currentUser){
    isDisplay = false;
    std::vector<std::string> options = {"Delete", "Return"};
    int selectedOption = 0;
    while(true){
        SYSTEM;
        CLEAR;
        displayDeleteMovieBanner();

        std::cout << "Title: " << movie.name << std::endl;
        std::cout << "Release date: " << movie.released << "\n\n";
        std::cout << "Description\n" << movie.description << "\n\n";
        std::cout << "$" << movie.price << " | " << movie.stock << " in stock\n" << std::endl;

        for (int i = 0; i < options.size(); ++i) {
            if (i == selectedOption) {
                ConsoleAppearance::SetColor(0, 7);
                std::cout << " " << options[i] << " " << std::endl;
                ConsoleAppearance::SetColor(7, 0);
            } else {
                ConsoleAppearance::SetColor(7, 0);
                std::cout << " " << options[i] << std::endl;
            }
        }
#ifdef _WIN32
        int key = GETCH;

        if (key == 224) { 
            key = GETCH;
            if (key == 72) {
                selectedOption = (selectedOption - 1 + options.size()) % options.size();
            } else if (key == 80) {
                selectedOption = (selectedOption + 1) % options.size();
            }
        } else if (key == 13) {
            if (options[selectedOption] == "Delete") {
                movie.deleteFromDb();
                std::cout << "Movie deleted successfully!" << std::endl;
                return;
            } else if (options[selectedOption] == "Return") {
                break;
            }
        } else if (key == 27) {
            return;
        }
#elif _WIN64
        int key = GETCH;

        if (key == 224) { 
            key = GETCH;
            if (key == 72) {
                selectedOption = (selectedOption - 1 + options.size()) % options.size();
            } else if (key == 80) {
                selectedOption = (selectedOption + 1) % options.size();
            }
        } else if (key == 13) {
            if (options[selectedOption] == "Delete") {
                movie.deleteFromDb();
                std::cout << "Movie deleted successfully!" << std::endl;
                return;
            } else if (options[selectedOption] == "Return") {
                break;
            }
        } else if (key == 27) {
            return;
        }
#else
        initscr();
        noecho();
        cbreak();
        keypad(stdscr, TRUE);

        int key = GETCH;

        endwin();

        if (key == KEY_UP) {
            selectedOption = (selectedOption - 1 + options.size()) % options.size();
        } else if (key == KEY_DOWN) {
            selectedOption = (selectedOption + 1) % options.size();
        } else if (key == 10) { 
            if (options[selectedOption] == "Delete") {
                movie.deleteFromDb();
                std::cout << "Movie deleted successfully!" << std::endl;
                return;
            } else if (options[selectedOption] == "Return") {
                break;
            }
        } else if (key == "\027") {
            return;
        }
#endif
        }
}