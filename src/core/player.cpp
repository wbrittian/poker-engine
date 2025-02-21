/*player.cpp*/

//
// a player
//
// William Brittian
// 2025
//

#include "player.hpp"

void Player::emptyHand() {
    this->Cards.clear();
}

void Player::addCards(std::vector<Card> cards) {
    for (Card card : cards) {
        this->Cards.push_back(card);
    }
}

void Player::editCash(int amount) {
    this->Cash += amount;
}

void Player::setBet(int amount) {
    this->Bet = amount;
}

void Player::editBet(int amount) {
    this->Bet += amount;
}

void Player::resetBet() {
    this->Bet = 0;
}

void Player::editPotSplit(int amount) {
    this->PotSplit += amount;
}

void Player::resetPotSplit() {
    this->PotSplit = 0;
}

void Player::setNextPlayer(std::shared_ptr<Player> player) {
    this->Next = player;
}

Action Player::getAction(std::string cmd, int bet) {
    if (cmd == "c") {
        return {CALL, 0};
    } else if (cmd == "b" || cmd == "r") {
        std::string amt;
        std::cin >> amt;

        if (amt == "all") {
            return {BET, Cash};
            std::cout << "you go all in for " << Cash << std::endl;
        } else if (isInteger(amt)) { // isInteger(amt)
            int val = stoi(amt);

            if (val >= bet && val != 0) {
                if (bet > 0) {
                    std::cout << "you raise ";
                } else {
                    std::cout << "you bet ";
                }
                std::cout << val << std::endl;

                return {BET, val};
            } else {
                std::cout << "raise must be >= current bet" << std::endl;
            }
        } else {
            std::cout << "bet amount must be a nonzero integer" << std::endl;
        }
    } else if (cmd == "f") {
        return {FOLD, 0};
        std::cout << "you fold" << std::endl;
    }

    return {NONE, 0};
}

void Player::printCards() {
    this->Cards[0].printCard(true);
    std::cout << " ";
    this->Cards[1].printCard(true);
    std::cout << std::endl;
}

//
// accessors
//
std::vector<Card> Player::getCards() {
    return this->Cards;
}

std::string Player::getName() {
    return this->Name;
}

std::shared_ptr<Player> Player::getNextPlayer() {
    return this->Next;
}

int Player::getCash() {
    return this->Cash;
}

int Player::getBet() {
    return this->Bet;
}

int Player::getPotSplit() {
    return this->PotSplit;
}

//
// OVERRIDDEN BOT FUNCTIONS
//
// Action Player::getAction(int bet, int pot, int numPlaying) {
//     throw runtime_error("used overridden function as player");
// }