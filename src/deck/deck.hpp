/*deck.h*/

//
// a deck of cards
//
// William Brittian
// 2025
//

#pragma once

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

#include "card.hpp"

class Deck {
  private:
    std::vector<Card> Cards;

  public:
    void refillCards();

    Card drawCard();
    std::vector<Card> drawCards(int numCards);
};