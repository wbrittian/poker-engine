/*card.h*/

//
// a card
//
// William Brittian
// 2025
//

#pragma once

#include <iostream>

#include "../utils/functions.hpp"

enum Suit {
    SPADE,
    HEART,
    CLUB,
    DIAMOND
};

struct Card {
    int rank;
    enum Suit suit;

    void printCard(bool shortForm);
};