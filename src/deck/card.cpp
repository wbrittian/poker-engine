/*card.cpp*/

//
// a card
//
// William Brittian
// 2025
//

#include "card.hpp"

using namespace std;

// prints out the card value
// note that it does not create a new line after
void Card::printCard(bool shortForm) {
    if (shortForm) {
        string ranks[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
        int idx = this->rank - 1;
        string suit = matchToSymbol(this->suit);

        if (this->suit == "Hearts" || this->suit == "Diamonds") {
            setColor("red");
            cout << ranks[idx] << suit;
            setColor("black");
        } else {
            cout << ranks[idx] << suit;
        }
    } else {
        string ranks[13] = {
            "Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"};
        int idx = this->rank - 1;

        cout << ranks[idx] << " of " << this->suit;
    }
}