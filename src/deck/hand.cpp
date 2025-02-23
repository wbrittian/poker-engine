/*hand.cpp*/

//
// enum for hand types
//
// William Brittian
// 2025
//

#include <map>

#include "hand.hpp"

void Hand::evaluateHand() {
    std::vector<Card> cards = this->CommunityCards;
    cards.push_back(this->PlayerCards[0]);
    cards.push_back(this->PlayerCards[1]);

    std::map<int, int> ranks;
    std::map<
}