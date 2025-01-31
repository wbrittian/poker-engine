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
#include "deck.h"

using namespace std;

class Game {

private:

    // general info
    vector<Player> Players;
    Deck Deck;

    Player* BigBlind;
    Player* LittleBlind;

    // round-specific
    vector<Player*> ActivePlayers;
    int Pot;
    int Bet;

public:

    void initializeGame(int numPlayers, int startingCash);
    void resetGame();
    void addPlayer(Player player);

    void dealToPlayer(Player& player);

    Player getCurrentLeader();

};