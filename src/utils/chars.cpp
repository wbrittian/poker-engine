/*chars.cpp*/

//
// a list of unicode characters and associated functions
//
// William Brittian
// 2025
//

#include "chars.hpp"

char16_t _spade = u'\u2660';
char16_t _heart = u'\u2665';
char16_t _club = u'\u2663';
char16_t _diamond = u'\u2666';
char16_t _chip = u'\u26C0';
char16_t _chips = u'\u26C1';

std::string spade = to_utf8(_spade);
std::string heart = to_utf8(_heart);
std::string club = to_utf8(_club);
std::string diamond = to_utf8(_diamond);
std::string chip = to_utf8(_chip);
std::string chips = to_utf8(_chips);

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

std::string matchToSymbol(Suit suit) {
    if (suit == SPADES) {
        return spade;
    } else if (suit == HEARTS) {
        return heart;
    } else if (suit == CLUBS) {
        return club;
    } else if (suit == DIAMONDS) {
        return diamond;
    } else {
        return "";
    }
}