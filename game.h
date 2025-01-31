/*game.h*/

//
// a poker game
//
// William Brittian
// 2025
//

#pragma once

#include <vector>

#include "player.h"

using namespace std;

class Game {

private:

    vector<Player> Players;

    int Pot;

public:

    Player getCurrentLeader();

};