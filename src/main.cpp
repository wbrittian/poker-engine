/*main.cpp*/

//
// William Brittian
// 2025
//

#include <iostream>
#include <vector>

#include "cli/cli.hpp"
#include "core/engine.hpp"


int main() {
    int NUM_PLAYERS = 6;

    CLI cli;
    PokerEngine engine;

    EngineSettings settings = cli.startup(NUM_PLAYERS);

    engine.initializeEngine(settings, NUM_PLAYERS);
    cli.runGame(engine);
}