/*hand.cpp*/

//
// enum for hand types
//
// William Brittian
// 2025
//

#include "hand.hpp"

void Hand::evaluateHand() {
    std::map<Rank, int> ranks;
    std::map<Suit, int> suits;

    for (Card card : Cards) {
        if(ranks[card.Rank] >= 3 && Type <= FOUR_OF_A_KIND) {
            Type = FOUR_OF_A_KIND;
        } else if (ranks[card.Rank] >= 2 && Type <- THREE_OF_A_KIND) {
            Type = THREE_OF_A_KIND;
        } else if (ranks[card.Rank] >= 1 && Type <= PAIR) {
            Type = PAIR;
        }

        if(suits[card.Suit] >= 4 && Type <= FLUSH) {
            
        }

        ranks[card.Rank]++;
        suits[card.Suit]++;
    }
}