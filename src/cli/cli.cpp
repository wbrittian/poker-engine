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
    std::string spade = _spade();
    std::string heart = _heart();
    std::string club = _club();
    std::string diamond = _diamond();
    std::string chip = _chip();

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

void CLI::createBots(const int& numBots) {
    for (int id = 1; id < numBots + 1; id++) {
        Bots.push_back(Bot(id));
        Names.push_back("Bot " + std::to_string(id));
    }
}

void CLI::printHelp() {
    std::cout << "----------------------------" << std::endl;
    std::cout << "............HELP............";
    std::cout << std::endl << std::endl << std::endl << std::endl << std::endl;
    std::cout << "h -> get list of available commands" << std::endl
              << "c -> call the current bet or check" << std::endl
              << "b/r [AMOUNT] -> bet (or raise) the given amount" << std::endl
              << "f -> fold your hand" << std::endl;
    std::cout << std::endl << std::endl << std::endl << std::endl;
    std::cout << "----------------------------" << std::endl;

    std::cin.get();
}

void CLI::printState(const PublicState& state, const PlayerState& pstate) {
    std::cout << "----------------------------" << std::endl;
    std::cout << "Hand " << state.HandNum << " ";
    switch (state.EngineStage) {
        case PREFLOP:
            std::cout << "Preflop";
            break;
        case FLOP:
            std::cout << "Flop";
            break;
        case TURN:
            std::cout << "Turn";
            break;
        case RIVER:
            std::cout << "River";
            break;
        case SHOWDOWN:
            std::cout << "Showdown";
            break;
    }
    std::cout << std::endl << std::endl;

    std::cout << "Pot: " << state.Pot << std::endl;
    std::cout << "Bet: " << state.CurrentBet << std::endl;
    std::cout << std::endl;
    
    for (int i = 0; i < state.Players.size(); i++) {
        Seat cur = state.Players[i];
        if (i == state.Current) {
            std::cout << "> ";
        } else {
            std::cout << "  ";
        }

        if (!cur.Active) {
            setColor("grey");
        }

        std::cout << Names[i] << " (";
        
        if (cur.Active) {
            setColor("green");
        }

        std::cout << cur.Cash << _chip();

        if (cur.Active) {
            setColor("black");
        }

        std::cout << "): ";

        if (cur.Active) {
            setColor("purple");
        }

        std::cout << cur.Bet << _chip();

        setColor("black");
        std::cout << std::endl;
    }

    std::cout << std::endl << "Community cards: ";
    printCards(state.Community);
    std::cout << std::endl << "Your cards: ";
    printCards(pstate.Hand);
    std::cout << std::endl << std::endl;
}

void CLI::printCards(const std::vector<Card>& cards) {
    for (const Card& card : cards) {
        printCard(card);
        std::cout << " ";
    }
}

Action CLI::getAction(const int& toPlay) {
    
    std::cout << toPlay << " to call > ";

    std::string line;
    std::string cmd, s_amt;

    std::getline(std::cin, line);
    std::istringstream iss(line);
    iss >> cmd >> s_amt;

    if (cmd == "h") {
        printHelp();
    } else if (cmd == "c") {
        return Action{Id, BET, 0};
    } else if (cmd == "b" || cmd == "r") {
        int amt = std::stoi(s_amt);
        return Action{Id, BET, amt};
    } else if (cmd == "f") {
        return Action{Id, FOLD};
    }
        
    return Action{Id, NONE};  
}

//
// public functions
//

EngineSettings CLI::startup(const int& numPlayers) {
    // TODO: change to constructor?
    printTitle();
    getName();

    Id = 0;
    Names.push_back(Name);
    createBots(numPlayers - 1);

    return getSettings();
}

void CLI::runGame(PokerEngine engine) {
    Engine = engine;

    while (true) {
        PublicState state = Engine.getPublicState();
        PlayerState pstate = Engine.getPlayerState(Id);
        printState(state, pstate);
        
        if (state.Current == Id) {
            Action action = getAction(state.CurrentBet - state.Players[Id].Bet);
            Engine.submitAction(action);
        } else {
            Action action = Bots[state.Current - 1].getAction(state);
            Engine.submitAction(action);
            std::cin.get();
        }
    }
}