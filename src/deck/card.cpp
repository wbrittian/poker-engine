/*card.cpp*/

//
// a card
//
// William Brittian
// 2025
//

#include "card.hpp"

// prints out the card value
// note that it does not create a new line after
void Card::printCard(bool shortForm) {
    if (shortForm) {
        std::string ranks[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
        int idx = this->rank - 1;
        std::string suit = matchToSymbol(this->suit);

        if (this->suit == "Hearts" || this->suit == "Diamonds") {
            setColor("red");
            std::cout << ranks[idx] << suit;
            setColor("black");
        } else {
            std::cout << ranks[idx] << suit;
        }
    } else {
        std::string ranks[13] = {
            "Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"};
        int idx = this->rank - 1;

        std::cout << ranks[idx] << " of " << this->suit;
    }
}