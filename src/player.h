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

using namespace std;

class Player {

private:

    string Name;

    vector<Card> Cards;

    int Cash;
    int Bet;
    int PotSplit;

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

    Action getAction();

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