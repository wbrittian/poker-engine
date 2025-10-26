/*cli.cpp*/

//
// the main cli runner
//
// William Brittian
// 2025
//

#include <iostream>
#include <string>

#include "functions.cpp"

// prints out the main title screen
void printTitle() {
    std::cout << std::endl;
    std::cout << "----------------------------" << std::endl;
    std::cout << "         Welcome to         " << std::endl;
    std::cout << std::endl;
    std::cout << "****************************" << std::endl;

    std::cout << spade << spade << spade << spade << "  " << heart << heart << heart << heart
              << "  " << chip << "  " << chip << "  " << club << club << club << club << "  "
              << diamond << diamond << diamond << diamond << std::endl;

    std::cout << spade << "  " << spade << "  " << heart << "  " << heart << "  " << chip << " "
              << chip << "   " << club << "     " << diamond << "  " << diamond << std::endl;

    std::cout << spade << spade << spade << spade << "  " << heart << "  " << heart << "  " << chip
              << chip << "    " << club << club << club << club << "  " << diamond << diamond
              << diamond << diamond << std::endl;

    std::cout << spade << "     " << heart << "  " << heart << "  " << chip << " " << chip << "   "
              << club << "     " << diamond << " " << diamond << " " << std::endl;

    std::cout << spade << "     " << heart << heart << heart << heart << "  " << chip << "  "
              << chip << "  " << club << club << club << club << "  " << diamond << "  " << diamond
              << std::endl;

    std::cout << "****************************" << std::endl;
    std::cout << std::endl;
    std::cout << "   William Brittian 2025    " << std::endl;
    std::cout << "----------------------------" << std::endl;
    std::cout << std::endl;
}

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

void startup() {

}

void runGame() {
    
}