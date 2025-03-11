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
    std::string suit = matchToSymbol(Suit);

    if (Suit == HEARTS || Suit == DIAMONDS) {
        setColor("red");
        std::cout << ranks[Rank] << suit;
        setColor("black");
    } else {
        std::cout << ranks[Rank] << suit;
    }  
}

std::string matchToSymbol(Suit suit) {
    if (suit == SPADES) {
        return spade;
    } else if (suit == HEARTS) {
        return heart;
    } else if (suit == CLUBS) {
        return club;
    } else if (suit == DIAMONDS) {
        return diamond;
    } else {
        return "";
    }
}