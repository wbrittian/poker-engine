/*main.cpp*/

//
// William Brittian
// 2025
//

#include <iostream>
#include <vector>

#include "game.h"
#include "player.h"
#include "chars.h"
#include "functions.h"

using namespace std;

int main() {

    int NUM_BOTS = 3;
    int STARTING_CASH = 500;

    string name;
    Game game;

    printTitle();
    name = getName();

    Player* player = new Player(name, STARTING_CASH);
    game.initializeGame(player, NUM_BOTS, STARTING_CASH);


    //
    // main game loop
    //


}