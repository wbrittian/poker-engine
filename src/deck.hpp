/*deck.h*/

//
// a deck of cards
//
// William Brittian
// 2025
//

#pragma once

#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <iostream>

#include "card.hpp"

using namespace std;

class Deck {

private:

    vector<Card> Cards;

public:

    void refillCards();

    Card drawCard();
    vector<Card> drawCards(int numCards);

};