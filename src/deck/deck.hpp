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

using namespace std;

class Deck {

private:

    vector<Card> Cards;

public:

    void refillCards();

    Card drawCard();
    vector<Card> drawCards(int numCards);

};