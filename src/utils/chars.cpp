/*chars.cpp*/

//
// a list of unicode characters and associated functions
//
// William Brittian
// 2025
//

#include "chars.hpp"

char16_t spade = u'\u2660';
char16_t heart = u'\u2665';
char16_t club = u'\u2663';
char16_t diamond = u'\u2666';
char16_t chip = u'\u26C0';
char16_t chips = u'\u26C1';

std::string SPADE = to_utf8(spade);
std::string HEART = to_utf8(heart);
std::string CLUB = to_utf8(club);
std::string DIAMOND = to_utf8(diamond);
std::string CHIP = to_utf8(chip);
std::string CHIPS = to_utf8(chips);

// converts char16_t unicode chars to strings that can be
// outputted by the console
std::string to_utf8(char16_t ch) {
    std::string utf8;
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

std::string matchToSymbol(std::string suit) {
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