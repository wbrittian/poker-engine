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

using namespace std;

extern string SPADE;
extern string CARD;

void printTitle();

string char16_to_utf8(char16_t ch);
string char32_to_utf8(char32_t ch);