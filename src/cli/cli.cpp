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
    using namespace ftxui;

    auto document = vbox({
        text(" COMMANDS") | bold,
        separator(),
        text(" h            show this help menu"),
        text(" c            call the current bet or check"),
        text(" r/b AMOUNT   raise (or bet) the given amount"),
        text(" f            fold your hand"),
    }) | border;

    auto screen = Screen::Create(Dimension::Full(), Dimension::Fit(document));
    Render(screen, document);
    std::cout << std::endl << screen.ToString() << std::endl;
    std::cout << "[press enter]";
    std::cin.get();
}

ftxui::Element CLI::cardElement(const Card& card) {
    using namespace ftxui;
    auto s = cardString(card);
    if (card.Suit == HEARTS || card.Suit == DIAMONDS) {
        return text(s) | color(Color::Red);
    }
    return text(s);
}

void CLI::printState(const PublicState& state, const PlayerState& pstate) {
    using namespace ftxui;

    std::string stage;
    switch (state.EngineStage) {
        case PREFLOP:   stage = "Preflop";  break;
        case FLOP:      stage = "Flop";     break;
        case TURN:      stage = "Turn";     break;
        case RIVER:     stage = "River";    break;
        case SHOWDOWN:  stage = "Showdown"; break;
        default:        stage = "";         break;
    }

    int sbIdx = state.SmallBlind;
    int bbIdx = (state.SmallBlind + 1) % (int)state.Players.size();

    // header
    auto header = vbox({
        hbox({text(" Hand "), text(std::to_string(state.HandNum)) | bold,
              text(" | "), text(stage) | bold}),
        hbox({text(" Pot: "),
              text(std::to_string(state.Pot) + _chip()) | color(Color::Green),
              text("   Bet: "),
              text(std::to_string(state.CurrentBet) + _chip()) | color(Color::Magenta)}),
    });

    // column widths
    const int W_NAME = 16;
    const int W_VAL  = 9;
    const int W_TAG  = 9;

    // column header row
    auto colHeader = hbox({
        text("  "),
        text("Name")    | size(WIDTH, EQUAL, W_NAME),
        text("Cash")    | size(WIDTH, EQUAL, W_VAL) | dim,
        text("Bet")     | size(WIDTH, EQUAL, W_VAL) | dim,
        text("In")      | size(WIDTH, EQUAL, W_VAL) | dim,
    });

    // player rows
    Elements playerRows;
    playerRows.push_back(colHeader);
    for (int i = 0; i < (int)state.Players.size(); i++) {
        const Seat& cur = state.Players[i];

        auto cursor = text(i == state.Current ? "> " : "  ");
        auto nameCell = text(Names[i]) | size(WIDTH, EQUAL, W_NAME);

        Element cashCell, betCell, inCell, statusCell;

        if (cur.Active) {
            cashCell   = text(std::to_string(cur.Cash) + _chip())
                         | color(Color::Green) | size(WIDTH, EQUAL, W_VAL);
            betCell    = (cur.Bet > 0
                         ? text(std::to_string(cur.Bet) + _chip()) | color(Color::Magenta)
                         : text("-"))
                         | size(WIDTH, EQUAL, W_VAL);
            inCell     = (cur.PotSplit > 0
                         ? text(std::to_string(cur.PotSplit) + _chip()) | color(Color::Blue)
                         : text("-"))
                         | size(WIDTH, EQUAL, W_VAL);
            statusCell = cur.Cash == 0
                         ? text("[ALL IN]") | color(Color::Yellow) | size(WIDTH, EQUAL, W_TAG)
                         : text("") | size(WIDTH, EQUAL, W_TAG);
        } else {
            cashCell   = text("[FOLDED]") | dim | size(WIDTH, EQUAL, W_VAL);
            betCell    = text("-")        | dim | size(WIDTH, EQUAL, W_VAL);
            inCell     = (cur.PotSplit > 0
                         ? text(std::to_string(cur.PotSplit) + _chip()) | color(Color::Blue)
                         : text("-") | dim)
                         | size(WIDTH, EQUAL, W_VAL);
            statusCell = text("") | size(WIDTH, EQUAL, W_TAG);
        }

        Element blindTag = text("") | size(WIDTH, EQUAL, 5);
        if (i == sbIdx)      blindTag = text("[SB]") | color(Color::Cyan)   | size(WIDTH, EQUAL, 5);
        else if (i == bbIdx) blindTag = text("[BB]") | color(Color::Yellow) | size(WIDTH, EQUAL, 5);

        playerRows.push_back(hbox({cursor, nameCell, cashCell, betCell, inCell, statusCell, blindTag}));
    }

    // community cards
    Elements community;
    community.push_back(text(" Community:  "));
    if (state.Community.empty()) {
        community.push_back(text("-"));
    } else {
        for (const Card& c : state.Community) {
            community.push_back(cardElement(c));
            community.push_back(text(" "));
        }
    }

    // your hand
    Elements hand;
    hand.push_back(text(" Your hand:  "));
    for (const Card& c : pstate.Hand) {
        hand.push_back(cardElement(c));
        hand.push_back(text(" "));
    }

    auto document = vbox({
        header,
        separator(),
        vbox(playerRows),
        separator(),
        hbox(community),
        hbox(hand),
    }) | border;

    clearScreen();
    auto screen = Screen::Create(Dimension::Full(), Dimension::Fit(document));
    Render(screen, document);
    std::cout << screen.ToString() << std::endl;
}

void CLI::printResults(const ResultState& results) {
    using namespace ftxui;

    Elements content;
    content.push_back(
        text(" " + Names[results.Winner] + " wins " + _chip() + std::to_string(results.Pot) + "!")
        | color(Color::Yellow) | bold
    );

    if (!results.Hands.empty()) {
        content.push_back(separator());
        for (int i = 0; i < (int)results.Players.size(); i++) {
            int pid = results.Players[i];
            Elements row;
            row.push_back(text(" " + Names[pid] + ":  "));
            for (const Card& c : results.Hands[i]) {
                row.push_back(cardElement(c));
                row.push_back(text(" "));
            }
            content.push_back(hbox(row));
        }
    }

    auto document = vbox(content) | border;
    clearScreen();
    auto screen = Screen::Create(Dimension::Full(), Dimension::Fit(document));
    Render(screen, document);
    std::cout << screen.ToString() << std::endl;
    std::cout << "[press enter]";
    std::cin.get();
}

void CLI::printCards(const std::vector<Card>& cards) {
    for (const Card& card : cards) {
        printCard(card);
        std::cout << " ";
    }
}

Action CLI::getAction(const int& toPlay, const int& minRaise) {
    while (true) {
        if (toPlay == 0) {
            std::cout << "[c] check  [r] raise (min " << minRaise << _chip() << ")  [f] fold  [h] help" << std::endl;
            std::cout << "check > ";
        } else {
            std::cout << "[c] call (" << toPlay << _chip() << ")  [r] raise (min " << minRaise << _chip() << ")  [f] fold  [h] help" << std::endl;
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
            int minRaise = std::max(2 * state.CurrentBet, state.SmallBlind * 2);
            Action action = getAction(state.CurrentBet - state.Players[state.Current].Bet, minRaise);
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