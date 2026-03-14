/*functions.hpp*/

//
// helper functions for running game
//
// William Brittian
// 2025
//

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../core/deck/hand.hpp"

void setColor(const std::string& color);
void clearScreen();
std::string hline(int n = 50);
bool isInteger(const std::string& str);

std::string to_utf8(char16_t ch);

std::string _spade();
std::string _heart();
std::string _club();
std::string _diamond();
std::string _chip();
std::string _chips();

extern std::string ranks[13];

std::string matchToSymbol(Suit suit);
std::string cardString(const Card& card);
void printCard(Card card);