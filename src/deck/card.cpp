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
void Card::printCard() {
    std::string ranks[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    int idx = Rank - 1;
    std::string suit = matchToSymbol(Suit);

    if (Suit == Suit::HEARTS || Suit == Suit::DIAMONDS) {
        setColor("red");
        std::cout << ranks[idx] << suit;
        setColor("black");
    } else {
        std::cout << ranks[idx] << suit;
    }  
}