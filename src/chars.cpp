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

char32_t card = U'\U00010FB5';

string SPADE = char16_to_utf8(spade);
string HEART = char16_to_utf8(heart);
string CLUB = char16_to_utf8(club);
string DIAMOND = char16_to_utf8(diamond);
string CHIP = char16_to_utf8(chip);

string CARD = char32_to_utf8(card);

void printTitle() {
    

    cout << "****************************" << endl;

    cout << SPADE << SPADE << SPADE << SPADE << "  " << HEART << HEART << HEART << HEART << "  " << CHIP << "  " 
    << CHIP << "  " << CLUB << CLUB << CLUB << CLUB << "  " << DIAMOND << DIAMOND << DIAMOND << DIAMOND << endl;

    cout << SPADE << "  " << SPADE << "  " << HEART << "  " << HEART << "  " << CHIP << " " << CHIP << "   " 
    << CLUB << "     " << DIAMOND << "  " << DIAMOND << endl;

    cout << SPADE << SPADE << SPADE << SPADE << "  " << HEART << "  " << HEART << "  " << CHIP << CHIP << "    " 
    << CLUB << CLUB << CLUB << CLUB << "  " << DIAMOND << DIAMOND << DIAMOND << DIAMOND << endl;

    cout << SPADE << "     " << HEART << "  " << HEART << "  " << CHIP << " " << CHIP << "   " 
    << CLUB << "     " << DIAMOND << " " << DIAMOND << " " << endl;

    cout << SPADE << "     " << HEART << HEART << HEART << HEART << "  " << CHIP << "  " << CHIP << "  " 
    << CLUB << CLUB << CLUB << CLUB << "  " << DIAMOND << "  " << DIAMOND << endl;

    cout << "****************************" << endl;
    
}

string char16_to_utf8(char16_t ch) {
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

string char32_to_utf8(char32_t ch) {
    string utf8;
    if (ch <= 0x7F) {
        utf8 += static_cast<char>(ch);
    } else if (ch <= 0x7FF) {
        utf8 += static_cast<char>(0xC0 | ((ch >> 6) & 0x1F));
        utf8 += static_cast<char>(0x80 | (ch & 0x3F));
    } else if (ch <= 0xFFFF) {
        utf8 += static_cast<char>(0xE0 | ((ch >> 12) & 0x0F));
        utf8 += static_cast<char>(0x80 | ((ch >> 6) & 0x3F));
        utf8 += static_cast<char>(0x80 | (ch & 0x3F));
    } else {  // U+10000 to U+10FFFF (4-byte UTF-8)
        utf8 += static_cast<char>(0xF0 | ((ch >> 18) & 0x07));
        utf8 += static_cast<char>(0x80 | ((ch >> 12) & 0x3F));
        utf8 += static_cast<char>(0x80 | ((ch >> 6) & 0x3F));
        utf8 += static_cast<char>(0x80 | (ch & 0x3F));
    }
    return utf8;
}