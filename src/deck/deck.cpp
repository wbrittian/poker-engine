/*deck.cpp*/

//
// a deck of cards
//
// William Brittian
// 2025
//

#include "deck.hpp"

// empties deck and adds 52 cards back to it
void Deck::refillCards() {
    this->Cards.clear();

    // 2-10 are as normal
    // 1 = Ace, 11 = Jack, 12 = Queen, 13 = King
    std::vector<Rank> ranks = {ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING};
    std::vector<Suit> suits = {SPADES, HEARTS, CLUBS, DIAMONDS};

    for (int r = 0; r < ranks.size(); r++) {
        for (int s = 0; s < suits.size(); s++) {
            Card card;

            card.Rank = ranks[r];
            card.Suit = suits[s];

            this->Cards.push_back(card);
        }
    }
}

// draws a random card from the deck
Card Deck::drawCard() {
    if (this->Cards.size() == 0) {
        throw std::length_error("No more cards in deck");
    }

    srand(time(0));

    int idx = arc4random() % this->Cards.size();
    Card card = this->Cards[idx];

    this->Cards.erase(this->Cards.begin() + idx);

    return card;
}

// draws multiple cards from the deck
std::vector<Card> Deck::drawCards(int numCards) {
    std::vector<Card> cards;

    for (int i = 0; i < numCards; i++) {
        cards.push_back(this->drawCard());
    }

    return cards;
}