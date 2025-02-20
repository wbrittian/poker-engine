/*chars.cpp*/

//
// a list of unicode characters and associated functions
//
// William Brittian
// 2025
//

#include "chars.h"

using namespace std;

char16_t spade = u'\u2660';
char16_t heart = u'\u2665';
char16_t club = u'\u2663';
char16_t diamond = u'\u2666';
char16_t chip = u'\u26C0';
char16_t chips = u'\u26C1';

string SPADE = to_utf8(spade);
string HEART = to_utf8(heart);
string CLUB = to_utf8(club);
string DIAMOND = to_utf8(diamond);
string CHIP = to_utf8(chip);
string CHIPS = to_utf8(chips);

// converts char16_t unicode chars to strings that can be
// outputted by the console
string to_utf8(char16_t ch) {
    string utf8;
    if (ch <= 0x7F) { // 1-byte UTF-8
        utf8.push_back(static_cast<char>(ch));
    } else if (ch <= 0x7FF) { // 2-byte UTF-8
        utf8.push_back(static_cast<char>(0xC0 | ((ch >> 6) & 0x1F)));
        utf8.push_back(static_cast<char>(0x80 | (ch & 0x3F)));
    } else { // 3-byte UTF-8
        utf8.push_back(static_cast<char>(0xE0 | ((ch >> 12) & 0x0F)));
        utf8.push_back(static_cast<char>(0x80 | ((ch >> 6) & 0x3F)));
        utf8.push_back(static_cast<char>(0x80 | (ch & 0x3F)));
    }
    return utf8;
}

string matchToSymbol(string suit) {
    if (suit == "Spades") {
        return SPADE;
    } else if (suit == "Hearts") {
        return HEART;
    } else if (suit == "Clubs") {
        return CLUB;
    } else if (suit == "Diamonds") {
        return DIAMOND;
    } else {
        return "";
    }
}