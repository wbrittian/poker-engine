/*functions.cpp*/

//
// helper functions for running game
//
// William Brittian
// 2025
//

#include "functions.hpp"

// gets player name from terminal
std::string getName() {
    std::string name;
    bool correct = false;

    while (!correct) {
        std::cout << "please enter your name:" << std::endl;
        std::getline(std::cin, name);
        std::cout << std::endl;

        std::string ans;
        std::cout << "does this look right (y/n)? " << name << std::endl;
        std::getline(std::cin, ans);
        std::cout << std::endl;

        if (ans == "y") {
            correct = true;
        }
    }

    return name;
}

// prints out the main title screen
void printTitle() {
    std::cout << std::endl;
    std::cout << "----------------------------" << std::endl;
    std::cout << "         Welcome to         " << std::endl;
    std::cout << std::endl;
    std::cout << "****************************" << std::endl;

    std::cout << SPADE << SPADE << SPADE << SPADE << "  " << HEART << HEART << HEART << HEART
              << "  " << CHIP << "  " << CHIP << "  " << CLUB << CLUB << CLUB << CLUB << "  "
              << DIAMOND << DIAMOND << DIAMOND << DIAMOND << std::endl;

    std::cout << SPADE << "  " << SPADE << "  " << HEART << "  " << HEART << "  " << CHIP << " "
              << CHIP << "   " << CLUB << "     " << DIAMOND << "  " << DIAMOND << std::endl;

    std::cout << SPADE << SPADE << SPADE << SPADE << "  " << HEART << "  " << HEART << "  " << CHIP
              << CHIP << "    " << CLUB << CLUB << CLUB << CLUB << "  " << DIAMOND << DIAMOND
              << DIAMOND << DIAMOND << std::endl;

    std::cout << SPADE << "     " << HEART << "  " << HEART << "  " << CHIP << " " << CHIP << "   "
              << CLUB << "     " << DIAMOND << " " << DIAMOND << " " << std::endl;

    std::cout << SPADE << "     " << HEART << HEART << HEART << HEART << "  " << CHIP << "  "
              << CHIP << "  " << CLUB << CLUB << CLUB << CLUB << "  " << DIAMOND << "  " << DIAMOND
              << std::endl;

    std::cout << "****************************" << std::endl;
    std::cout << std::endl;
    std::cout << "   William Brittian 2025    " << std::endl;
    std::cout << "----------------------------" << std::endl;
    std::cout << std::endl;
}

void setColor(std::string color) {
    if (color == "red") {
        std::cout << "\033[31m";
    } else if (color == "green") {
        std::cout << "\033[32m";
    } else if (color == "blue") {
        std::cout << "\033[34m";
    } else if (color == "purple") {
        std::cout << "\033[35m";
    } else if (color == "black") {
        std::cout << "\033[0m";
    }
}

bool isInteger(const std::string& str) {
    std::stringstream ss(str);
    int i;
    char c;
    return (ss >> i) && (ss >> c).eof();
}