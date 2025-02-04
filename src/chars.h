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
extern string HEART;
extern string CLUB;
extern string DIAMOND;
extern string CHIP;
extern string CHIPS;

void printTitle();

string to_utf8(char16_t ch);