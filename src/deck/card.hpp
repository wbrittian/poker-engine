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
#include "../utils/chars.hpp"

enum Rank {
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING,
    ACE
};

enum Suit {
    SPADES,
    HEARTS,
    CLUBS,
    DIAMONDS
};

struct Card {
    Rank Rank;
    Suit Suit;

    void printCard();
};

std::string matchToSymbol(Suit suit);