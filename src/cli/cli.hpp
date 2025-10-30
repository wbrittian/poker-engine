/*cli.hpp*/

//
// the main cli runner
//
// William Brittian
// 2025
//

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../core/engine.hpp"
#include "../bots/bot.hpp"
#include "functions.hpp"

class CLI {
  private:
    PokerEngine Engine;
    std::vector<Bot> Bots;
    std::vector<std::string> Names;

    std::string Name;
    int Id = 0;

    void printTitle();
    void getName();
    EngineSettings getSettings();
    void createBots(const int& numBots);
    void printHelp();
    // void printState(const PublicState& state);
    void printCards(const std::vector<Card>& cards);
    Action getAction(const int& toPlay);

  public:
    EngineSettings startup(const int& numPlayers);
    void runGame(PokerEngine engine);

    void printState(const PublicState& state, const PlayerState& pstate);
};