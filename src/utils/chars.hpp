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

extern std::string spade;
extern std::string heart;
extern std::string club;
extern std::string diamond;
extern std::string chip;
extern std::string chips;

void printTitle();
std::string to_utf8(char16_t ch);