/*card.h*/

//
// a card
//
// William Brittian
// 2025
//

#pragma once

#include <iostream>
#include <string>

#include "../utils/functions.hpp"

struct Card {
    int rank;
    std::string suit;

    void printCard(bool shortForm);
};