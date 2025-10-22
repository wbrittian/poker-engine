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

#include "../deck/card.hpp"
#include "../deck/hand.hpp"
#include "../utils/action.h"
#include "../utils/functions.hpp"

class Player {
  protected:
    std::string Name;
    int id;

    Hand Hand;

    int Cash;
    int Bet = 0;
    int PotSplit = 0;

  public:
    Player(std::string name, int startingCash)
        : Name(name)
        , Cash(startingCash)
        , Bet(0)
        , PotSplit(0) {}

    virtual ~Player() = default;

    void addCards(std::vector<Card> cards);

    void editCash(int amount);
    void setBet(int amount);
    void editBet(int amount);
    
    void editPotSplit(int amount);

    void resetHand();
    void resetBet();
    void resetPotSplit();

    virtual Action getAction(std::string cmd, int bet);

    void printCards();

    //
    // accessors
    //
    std::vector<Card> getCards();
    std::string getName();
    int getCash();
    int getBet();
    int getPotSplit();
    struct Hand getHand();

    //
    // OVERRIDDEN BOT FUNCTIONS
    //
    // virtual Action getAction(int bet, int pot, int numPlaying);
};