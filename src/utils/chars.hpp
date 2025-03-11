/*chars.h*/

//
// a list of unicode characters and associated functions
//
// William Brittian
// 2025
//

#pragma once

#include <iostream>
#include <string>

#include "../deck/card.hpp"

extern std::string SPADE;
extern std::string HEART;
extern std::string CLUB;
extern std::string DIAMOND;
extern std::string CHIP;
extern std::string CHIPS;

void printTitle();

std::string to_utf8(char16_t ch);

std::string matchToSymbol(Suit suit);