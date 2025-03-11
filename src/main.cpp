/*main.cpp*/

//
// William Brittian
// 2025
//

#include <iostream>
#include <vector>

#include "core/game.hpp"
#include "core/player.hpp"

int main() {
    int NUM_BOTS = 3;
    int STARTING_CASH = 500;

    std::string name;
    Game game;

    printTitle();
    name = getName();

    std::shared_ptr<Player> player = std::make_shared<Player>(name, STARTING_CASH);
    game.initializeGame(player, NUM_BOTS, STARTING_CASH);

    game.runGame();
}