/*card.cpp*/

//
// a card
//
// William Brittian
// 2025
//

#include "card.h"

using namespace std;

void Card::printCard(bool shortForm) {
    if (shortForm) {
        string ranks[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

    } else {
        string ranks[13] = {"Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"};
        int idx = this->rank - 1;

        cout << ranks[idx] << " of " << this->suit << endl;
    }
}