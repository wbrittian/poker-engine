/*player.h*/

//
// a player
//
// William Brittian
// 2025
//

#pragma once

#include <string>
#include <vector>

#include "card.h"

using namespace std;

class Player {

private:

    vector<Card> Cards;
    int Cash;

public:

    Player(int startingCash)
        : Cash(startingCash)
        {}

    void emptyHand();
    void addCards(vector<Card> cards);

    void editCash(int amount);

    //
    // accessors
    //
    vector<Card> getCards();

    int getCash();

};