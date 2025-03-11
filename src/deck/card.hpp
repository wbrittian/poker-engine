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
    ACE,
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
    KING
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