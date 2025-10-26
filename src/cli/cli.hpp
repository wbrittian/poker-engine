/*cli.hpp*/

//
// the main cli runner
//
// William Brittian
// 2025
//

#include <iostream>
#include <string>
#include <vector>

#include "../core/engine.hpp"
#include "../bots/bot.hpp"
#include "functions.hpp"

class CLI {
  private:
    PokerEngine Engine;
    std::vector<Bot> Bots;

    std::string Name;
    int Id = 0;

    void printTitle();
    void getName();
    EngineSettings getSettings();
    void createBots(std::vector<int>& botIds);
    void printState(const PublicState& state);
    Action getAction();

  public:
    EngineSettings startup(std::vector<int>& pids);
    void runGame(PokerEngine engine);
};