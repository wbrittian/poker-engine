/*functions.cpp*/

//
// helper functions for running game
//
// William Brittian
// 2025
//

#include "functions.hpp"


void setColor(const std::string& color) {
    if (color == "red") {
        std::cout << "\033[31m";
    } else if (color == "green") {
        std::cout << "\033[32m";
    } else if (color == "blue") {
        std::cout << "\033[34m";
    } else if (color == "purple") {
        std::cout << "\033[35m";
    } else if (color == "black") {
        std::cout << "\033[0m";
    } else if (color == "grey") {
        std::cout << "\033[90m";
    }
}

bool isInteger(const std::string& str) {
    std::stringstream ss(str);
    int i;
    char c;
    return (ss >> i) && (ss >> c).eof();
}

//
// card printing
//

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

std::string _spade() {
    return to_utf8(u'\u2660');
}
std::string _heart() {
    return to_utf8(u'\u2665');
}
std::string _club() {
    return to_utf8(u'\u2663');
}
std::string _diamond() {
    return to_utf8(u'\u2666');
}
std::string _chip() {
    return to_utf8(u'\u26C0');
}
std::string _chips() {
    return to_utf8(u'\u26C1');
}

std::string matchToSymbol(Suit suit) {
    if (suit == SPADES) {
        return _spade();
    } else if (suit == HEARTS) {
        return _heart();
    } else if (suit == CLUBS) {
        return _club();
    } else if (suit == DIAMONDS) {
        return _diamond();
    } else {
        return "";
    }
}

std::string ranks[13] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
void printCard(Card card) {
    Suit suit = card.Suit;
    Rank rank = card.Rank;

    std::string suitSymbol = matchToSymbol(suit);

    if (suit == HEARTS || suit == DIAMONDS) {
        setColor("red");
        std::cout << ranks[rank] << suitSymbol;
        setColor("black");
    } else {
        std::cout << ranks[rank] << suitSymbol;
    }  
}