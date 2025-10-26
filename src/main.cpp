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
    CLI cli;
    PokerEngine engine;

    std::vector<int> ids;
    for (int i = 0; i < 6; i++) {
        ids.push_back(i);
    }

    EngineSettings settings = cli.startup(ids[0]);

    engine.initializeEngine(settings, ids);
    cli.runGame(engine);
}