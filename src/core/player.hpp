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
#include "../utils/action.h"
#include "../utils/functions.hpp"

class Player {
  protected:
    std::string Name;

    std::vector<Card> Cards;

    int Cash;
    int Bet = 0;
    int PotSplit = 0;

    Action CurrentAction;

    std::shared_ptr<Player> Next;

  public:
    Player(std::string name, int startingCash)
        : Name(name)
        , Cash(startingCash)
        , Bet(0)
        , PotSplit(0)
        , CurrentAction({NONE, 0}) {}

    virtual ~Player() = default;

    void emptyHand();
    void addCards(std::vector<Card> cards);

    void editCash(int amount);
    void setBet(int amount);
    void editBet(int amount);
    void resetBet();
    void editPotSplit(int amount);
    void resetPotSplit();

    void setNextPlayer(std::shared_ptr<Player> player);

    virtual Action getAction(std::string cmd, int bet);

    void printCards();

    //
    // accessors
    //
    std::vector<Card> getCards();
    std::string getName();
    std::shared_ptr<Player> getNextPlayer();
    int getCash();
    int getBet();
    int getPotSplit();

    //
    // OVERRIDDEN BOT FUNCTIONS
    //
    // virtual Action getAction(int bet, int pot, int numPlaying);
};