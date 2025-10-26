/*cli.cpp*/

//
// the main cli runner
//
// William Brittian
// 2025
//

#include "cli.hpp"

// prints out the main title screen
void CLI::printTitle() {
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
void CLI::getName() {
    bool correct = false;

    while (!correct) {
        std::cout << "please enter your name:" << std::endl;
        std::getline(std::cin, Name);
        std::cout << std::endl;

        std::string ans;
        std::cout << "does this look right (y/n)? " << Name << std::endl;
        std::getline(std::cin, ans);
        std::cout << std::endl;

        if (ans == "y") {
            correct = true;
        }
    }
}

EngineSettings CLI::getSettings() {
    EngineSettings settings;

    // TODO: add command line options for settings

    return settings;
}

void CLI::createBots(std::vector<int>& ids) {
    for (int id : ids) {
        Bots.push_back(Bot(id));
    }
}

void CLI::printState(const PublicState& state) {

}

Action CLI::getAction() {

}

//
// public functions
//

EngineSettings CLI::startup(std::vector<int>& pids) {
    // TODO: change to constructor?
    printTitle();
    getName();

    Id = pids [0];
    pids.erase(pids.begin());
    createBots(pids);

    return getSettings();
}

void CLI::runGame(PokerEngine engine) {
    Engine = engine;

    while (true) {
        const PublicState state = Engine.getPublicState();
        printState(state);
        
        Action action;
        if (state.Current == Id) {
            action = getAction();
        } else {
            action = Bots[state.Current].getAction(state);
        }

        Engine.submitAction(action);
    }
}