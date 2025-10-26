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
#include "functions.cpp"

class CLI {
  private:
    PokerEngine Engine;
    std::vector<Bot> Bots;

    std::string Name;
    int Id = 0;

    void printTitle();
    void getName();
    EngineSettings getSettings();

  public:
    EngineSettings startup(int pid);
    void runGame(PokerEngine engine);
};