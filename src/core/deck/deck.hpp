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

class Deck {
  private:
    std::vector<Card> Cards;

  public:
    void refillCards();

    Card drawCard();
    std::vector<Card> drawCards(int numCards);
};