/*card.h*/

//
// a card
//
// William Brittian
// 2025
//

#pragma once

#include <string>
#include <iostream>

#include "../utils/functions.hpp"

using namespace std;

struct Card {
    int rank;
    string suit;

    void printCard(bool shortForm);
};