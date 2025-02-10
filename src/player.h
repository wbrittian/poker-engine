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
#include "action.h"
#include "functions.h"

using namespace std;

class Player {

protected:

    string Name;

    vector<Card> Cards;

    int Cash;
    int Bet = 0;
    int PotSplit = 0;

    Action CurrentAction;

    Player* Next;

public:

    Player(string name, int startingCash)
        : Name(name), Cash(startingCash), Bet(0), PotSplit(0), CurrentAction({NONE, 0})
        {}

    void emptyHand();
    void addCards(vector<Card> cards);

    void editCash(int amount);

    void setNextPlayer(Player* player);

    virtual Action getAction(int bet);

    void printCards();

    //
    // accessors
    //
    vector<Card> getCards();
    int getCash();
    string getName();
    Player* getNextPlayer();
    int getBet();
    int getPotSplit();

};