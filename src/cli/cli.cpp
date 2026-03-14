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
    std::cout << "Enter your name: ";
    std::getline(std::cin, Name);
    std::cout << std::endl;
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
    std::cout << std::endl;
    std::cout << "\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550" << std::endl;
    std::cout << " COMMANDS" << std::endl;
    std::cout << "\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550" << std::endl;
    std::cout << " h            show this help menu" << std::endl;
    std::cout << " c            call the current bet or check" << std::endl;
    std::cout << " r/b AMOUNT   raise (or bet) the given amount" << std::endl;
    std::cout << " f            fold your hand" << std::endl;
    std::cout << "\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550" << std::endl;
    std::cout << std::endl << "[press enter]";
    std::cin.get();
}

void CLI::printState(const PublicState& state, const PlayerState& pstate) {
    clearScreen();

    std::string stage;
    switch (state.EngineStage) {
        case PREFLOP:   stage = "Preflop";  break;
        case FLOP:      stage = "Flop";     break;
        case TURN:      stage = "Turn";     break;
        case RIVER:     stage = "River";    break;
        case SHOWDOWN:  stage = "Showdown"; break;
        default:        stage = "";         break;
    }

    std::cout << "\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550" << std::endl;
    std::cout << " Hand " << state.HandNum << " | " << stage << std::endl;
    std::cout << " Pot: "; setColor("green"); std::cout << state.Pot << _chip(); setColor("black");
    std::cout << "   Bet: "; setColor("purple"); std::cout << state.CurrentBet << _chip(); setColor("black");
    std::cout << std::endl;
    std::cout << "\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550" << std::endl;
    std::cout << std::endl;

    for (int i = 0; i < (int)state.Players.size(); i++) {
        const Seat& cur = state.Players[i];

        if (i == state.Current) {
            std::cout << "> ";
        } else {
            std::cout << "  ";
        }

        if (!cur.Active) setColor("grey");

        // pad name to 14 chars
        std::string name = Names[i];
        std::cout << name;
        int pad = 14 - (int)name.size();
        for (int j = 0; j < pad; j++) std::cout << ' ';

        if (cur.Active) {
            setColor("green");
            std::cout << cur.Cash << _chip();
            setColor("black");
            std::cout << "  bet: ";
            if (cur.Bet > 0) {
                setColor("purple");
                std::cout << cur.Bet << _chip();
                setColor("black");
            } else {
                std::cout << "-";
            }
            if (cur.Cash == 0) {
                std::cout << "  ";
                setColor("yellow");
                std::cout << "[ALL IN]";
                setColor("black");
            }
        } else {
            setColor("grey");
            std::cout << "[FOLDED]";
            setColor("black");
        }

        std::cout << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Community:  ";
    if (state.Community.empty()) {
        std::cout << "-";
    } else {
        printCards(state.Community);
    }
    std::cout << std::endl;
    std::cout << "Your hand:  ";
    printCards(pstate.Hand);
    std::cout << std::endl << std::endl;
}

void CLI::printResults(const ResultState& results) {
    clearScreen();
    std::cout << "\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550" << std::endl;
    setColor("yellow");
    std::cout << " " << Names[results.Winner] << " wins " << _chip() << results.Pot << "!";
    setColor("black");
    std::cout << std::endl;
    std::cout << "\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550" << std::endl;

    if (!results.Hands.empty()) {
        std::cout << std::endl;
        for (int i = 0; i < (int)results.Players.size(); i++) {
            int pid = results.Players[i];
            std::string name = Names[pid];
            std::cout << " " << name << ": ";
            for (const Card& c : results.Hands[i]) {
                printCard(c);
                std::cout << " ";
            }
            std::cout << std::endl;
        }
    }

    std::cout << std::endl << "[press enter]";
    std::cin.get();
}

void CLI::printCards(const std::vector<Card>& cards) {
    for (const Card& card : cards) {
        printCard(card);
        std::cout << " ";
    }
}

Action CLI::getAction(const int& toPlay) {
    while (true) {
        if (toPlay == 0) {
            std::cout << "[c] check  [r] raise  [f] fold  [h] help" << std::endl;
            std::cout << "check > ";
        } else {
            std::cout << "[c] call (" << toPlay << _chip() << ")  [r] raise  [f] fold  [h] help" << std::endl;
            std::cout << "action > ";
        }

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
            try {
                int amt = std::stoi(s_amt);
                return Action{Id, BET, amt};
            } catch (...) {
                std::cout << "invalid amount" << std::endl;
            }
        } else if (cmd == "f") {
            return Action{Id, FOLD};
        }
    }
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
    int lastRound = 0;

    while (true) {
        PublicState state = Engine.getPublicState();

        if (state.EngineStage == INACTIVE) {
            printResults(Engine.getResultState());
            std::cout << "Game over! " << Names[state.Players[0].PlayerId] << " wins!" << std::endl;
            break;
        }

        if (state.HandNum != lastRound && lastRound != 0) {
            printResults(Engine.getResultState());
            lastRound = state.HandNum;
        } else if (lastRound == 0) {
            lastRound = state.HandNum;
        }

        PlayerState pstate = Engine.getPlayerState(Id);
        printState(state, pstate);

        int currentPid = state.Players[state.Current].PlayerId;

        if (currentPid == Id) {
            Action action = getAction(state.CurrentBet - state.Players[state.Current].Bet);
            Engine.submitAction(action);
        } else {
            Bot* bot = nullptr;
            for (Bot& b : Bots) {
                if (b.getId() == currentPid) {
                    bot = &b;
                    break;
                }
            }
            if (bot) {
                Action botAction = bot->getAction(state);
                Engine.submitAction(botAction);

                std::string botName = Names[state.Current];
                std::cout << botName << " ";
                if (botAction.Type == FOLD) {
                    std::cout << "folds.";
                } else if (botAction.Amount > 0) {
                    std::cout << "raises to " << botAction.Amount << _chip() << ".";
                } else if (state.CurrentBet == 0) {
                    std::cout << "checks.";
                } else {
                    std::cout << "calls " << state.CurrentBet << _chip() << ".";
                }
                std::cout << std::endl;
            }
            std::cout << "[press enter]";
            std::cin.get();
        }
    }
}