#include <iostream>
#include <string>


#include "menu.h"
#include "consoleapperance.h"
#include "offer.h"
#include "movies.h"
#include "users.h"


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
                if (movie.stock > 0 && &currentUser != 0) {
                    movie.rentMovie(currentUser.getId());
                    std::cout << "Your purchase was successful!" << std::endl;
                } else if(movie.stock == 0) {
                    ConsoleAppearance::SetColor(4, 0);
                    std::cout << "Out of stock!" <<  std::endl;
                    ConsoleAppearance::SetColor(7, 0);
                }else{
                    ConsoleAppearance::SetColor(4, 0);
                    std::cout << "\nYou must be logged in to do that" << std::endl;
                    ConsoleAppearance::SetColor(7, 0);
                }
                break;
            } else if (options[selectedOption] == "Return") {
                displayMovies(currentUser);
            }
        } else if (key == 27) {
            break;
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
                if (movie.stock > 0 && &currentUser != 0) {
                    movie.rentMovie(currentUser.getId());
                    std::cout << "Your purchase was successful!" << std::endl;
                } else if(movie.stock == 0) {
                    ConsoleAppearance::SetColor(4, 0);
                    std::cout << "Out of stock!" <<  std::endl;
                    ConsoleAppearance::SetColor(7, 0);
                }else{
                    ConsoleAppearance::SetColor(4, 0);
                    std::cout << "\nYou must be logged in to do that" << std::endl;
                    ConsoleAppearance::SetColor(7, 0);
                }
                break;
            } else if (options[selectedOption] == "Return") {
                break;
            }
        } else if (key == 27) {
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
                selectedOption = (selectedOption - 1 + options.size()) % options.size();
            } else if (key == KEY_DOWN) {
                selectedOption = (selectedOption + 1) % options.size();
            }
             else if (key == 10) {
                if (options[selectedOption] == "Rent") {
                    if (movie.stock > 0 && &currentUser != 0) {
                    movie.rentMovie(currentUser.getId());
                    std::cout << "Your purchase was successful!" << std::endl;
                } else if(movie.stock == 0) {
                    ConsoleAppearance::SetColor(4, 0);
                    std::cout << "Out of stock!" <<  std::endl;
                    ConsoleAppearance::SetColor(7, 0);
                }else{
                    ConsoleAppearance::SetColor(4, 0);
                    std::cout << "\nYou must be logged in to do that" << std::endl;
                    ConsoleAppearance::SetColor(7, 0);
                }
                    break;
                } else if (options[selectedOption] == "Return") {
                    break;
                }
            } else if (key == 27) {
                break;
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
    int selectedIndex = 0;
    while (true) {
        CLEAR;
        std::cout << "Select a movie using Up/Down arrows and press Enter:\n\n";
        for (int i = 0; i < movies.querySet.size(); ++i) {
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
                selectedIndex = (selectedIndex - 1 + movies.querySet.size()) % movies.querySet.size();
            } else if (key == 80) {
                selectedIndex = (selectedIndex + 1) % movies.querySet.size();
            }
        } else if (key == 13) {
            displayMovieDetails(movies.querySet[selectedIndex], currentUser);
            break;
        } else if (key == 27) { //Esc
            return;
        }
#elif _WIN64
    int key = GETCH;
        if (key == 224) {
            key = GETCH;
            if (key == 72) {
                selectedIndex = (selectedIndex - 1 + movies.querySet.size()) % movies.querySet.size();
            } else if (key == 80) {
                selectedIndex = (selectedIndex + 1) % movies.querySet.size();
            }
        } else if (key == 13) {
            displayMovieDetails(movies.querySet[selectedIndex]);
            break;
        } else if (key == 27) { //Esc
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
            selectedIndex = (selectedIndex - 1 + movies.querySet.size()) % movies.querySet.size();
        } else if (key == KEY_DOWN) {
            selectedIndex = (selectedIndex + 1) % movies.querySet.size();
        } else if (key == 10) { 
            displayMovieDetails(movies.querySet[selectedIndex]);
            break;
        } else if (key == 27) { 
            return;
        }
#endif
    }
    PAUSE;
}