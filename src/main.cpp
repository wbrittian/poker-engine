/*main.cpp*/

//
// William Brittian
// 2025
//

#include <iostream>
#include <vector>

#include "chars.hpp"
#include "functions.hpp"
#include "game.hpp"
#include "player.hpp"

using namespace std;

int main() {
    int NUM_BOTS = 3;
    int STARTING_CASH = 500;

    string name;
    Game game;

    printTitle();
    name = getName();

    shared_ptr<Player> player = make_shared<Player>(name, STARTING_CASH);
    game.initializeGame(player, NUM_BOTS, STARTING_CASH);

    //
    // main game loop
    //
}