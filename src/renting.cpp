#include <iostream>

#include "renting.h"
#include "menu.h"
#include "consoleapperance.h"
#include "offer.h"
#include "movies.h"
#include "users.h"
#include "banners.h"



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

void Renting::displayRentedMovieDetails(Movie& movie, User &currentUser){
    std::vector<std::string> options = {"Return", "Back"};
    int selectedOption = 0;
    while(true){
        SYSTEM;
        CLEAR;
        std::cout << std::string(movie.name.length() + 14, '=') << std::endl;
        std::cout << "||" << std::string(5, ' ') << movie.name << std::string(5, ' ') << "||" << std::endl;
        std::cout << std::string(movie.name.length() + 14, '=') << std::endl;

        std::cout << "Release date: " << movie.released << "\n\n";
        std::cout << "Description\n" << movie.description << "\n\n";
        std::cout << "Rent date: " << movie.getRentedDateHuman() << "\n\n";

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
            if (options[selectedOption] == "Return") {
                movie.unRentMovie(currentUser.getId());
                std::cout << "You have successfully returned the movie\n";
                PAUSE;
                break;
            }else if (options[selectedOption] == "Back") {
                break;
            }       
        }else if (key == 27) {
            return;
        }
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
            if (options[selectedOption] == "Return") {
                std::cout << "You have successfully returned the movie";
                break;
            }else if (options[selectedOption] == "Back") {
                break;
            }
        } else if (key == 27) {
            return;
        }
#else
        ESCDELAY = 50;
        initscr();
        noecho();
        cbreak();
        keypad(stdscr, TRUE);

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
            selectedOption = (selectedOption - 1 + options.size()) % options.size();
        } else if (key == KEY_DOWN) {
            selectedOption = (selectedOption + 1) % options.size();
        } else if (key == 27) {
            return;
        } else if (key == 10) {
            if (options[selectedOption] == "Return") {
                std::cout << "You have successfully returned the movie";
                break;
            } else if (options[selectedOption] == "Back") {
                break;
            }
        }
    }
#endif
}


void Renting::displayRentedMovies(User &currentUser){
    MoviesQuerySet movies("", currentUser.getId(), true, true);
    int selectedIndex = 0;
    while (true) {
        CLEAR;
        SYSTEM;
        displayRentalStatusBanner();
        std::cout << "Select a movie using Up/Down arrows and press Enter:\n\n";
        for (int i = 0; i < movies.querySet.size(); ++i) {
            if (i == selectedIndex) {
                ConsoleAppearance::SetColor(0, 7);
                std::cout << " " << movies.querySet[i].name << " | " << movies.querySet[i].getRentedDateHuman() << " " << "\n";
            } else {
                ConsoleAppearance::SetColor(7, 0);
                std::cout << movies.querySet[i].name << " | " << movies.querySet[i].getRentedDateHuman() << "\n";
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
            displayRentedMovieDetails(movies.querySet[selectedIndex], currentUser);
            break;
        } else if (key == 27) { //Esc
            break;
        }
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
            displayRentedMovieDetails(movies.querySet[selectedIndex]);
            break;
        } else if (key == 27) { //Esc
            break;
        }
}
#else
        ESCDELAY = 50;
        initscr();
        noecho();
        cbreak();
        keypad(stdscr, TRUE);

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
            selectedIndex = (selectedIndex - 1 + movies.querySet.size()) % movies.querySet.size();
        } else if (key == KEY_DOWN) {
            selectedIndex = (selectedIndex + 1) % movies.querySet.size();
        } else if (key == 10) { 
            displayRentedMovieDetails(movies.querySet[selectedIndex], currentUser);
            break;
        }
    }
#endif
}

void Renting::displayRentalHistory(User &currentUser) {
    CLEAR;
    SYSTEM;
    displayRentalHistoryBanner();
    if(currentUser.isAdmin){
        MoviesQuerySet movies("", -1, true, false);
        std::string renting;
        std::cout << "Username" << std::string(20, ' ') << "Title" << std::string(31, ' ') <<"Date"<< std::string(20, ' ') <<"Is in renting\n";
        for (int i = 0; i < movies.querySet.size(); ++i) {
            if(!movies.querySet[i].isInRenting){
                renting = "YES";
                ConsoleAppearance::SetColor(4, 0);
                std::cout << movies.querySet[i].rentedByLogin << std::string(20 - movies.querySet[i].rentedByLogin.length(), ' ')  <<  movies.querySet[i].name << std::string(36 - getTrueLength(movies.querySet[i].name), ' ') << movies.querySet[i].getRentedDateHuman() << std::string(13, ' ') << renting << "\n";
                ConsoleAppearance::SetColor(7, 0);
            }else{
                renting = "NO";
                std::cout << movies.querySet[i].rentedByLogin << std::string(20 - movies.querySet[i].rentedByLogin.length(), ' ')  <<  movies.querySet[i].name << std::string(36 - getTrueLength(movies.querySet[i].name), ' ') << movies.querySet[i].getRentedDateHuman() << std::string(13, ' ') << renting << "\n";
            }
        }
    }else{
        MoviesQuerySet movies("", currentUser.getId(), true, false);
        std::string renting;
        std::cout << "Title" << std::string(31, ' ') << "Date" << std::string(30, ' ') << "Is in renting\n";
        for (int i = 0; i < movies.querySet.size(); ++i) {
            if(!movies.querySet[i].isInRenting){
                renting = "YES";

            }else{
                renting = "NO";
            }
            std::cout <<  movies.querySet[i].name << std::string(36 - getTrueLength(movies.querySet[i].name), ' ') << movies.querySet[i].getRentedDateHuman() << std::string(15, ' ') << renting << "\n";
        }
    }
    std::cout<<"\n";
    PAUSE;
}