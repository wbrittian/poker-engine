/*player.cpp*/

//
// a player
//
// William Brittian
// 2025
//

#include "player.hpp"

void Player::resetHand() {
    Hand.Cards.clear();
}

void Player::addCards(std::vector<Card> cards) {
    for (Card card : cards) {
        this->Hand.Cards.push_back(card);
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
    Action action = {NONE, 0};
    setColor("blue");

    if (cmd == "c") {
        int amt = bet - this->Bet;
        if (amt == 0) {
            std::cout << "you check" << std::endl;
        } else {
            std::cout << "you call for " << amt << std::endl;
        }
        action.Type = BET;
    } else if (cmd == "b" || cmd == "r") {
        std::string amt;
        std::cin >> amt;

        if (amt == "all") {
            std::cout << "you go all in for " << Cash << std::endl;
            action = {BET, Cash};
        } else if (isInteger(amt)) { // isInteger(amt)
            int val = stoi(amt);

            if (val >= bet && val != 0) {
                if (bet > 0) {
                    std::cout << "you raise ";
                } else {
                    std::cout << "you bet ";
                }
                std::cout << val << std::endl;

                action = {BET, val};
            } else {
                std::cout << "raise must be >= current bet" << std::endl;
            }
        } else {
            std::cout << "bet amount must be a nonzero integer" << std::endl;
        }
    } else if (cmd == "f") {
        std::cout << "you fold" << std::endl;
        action.Type = FOLD;
    }

    setColor("black");
    return action;
}

void Player::printCards() {
    this->Hand.Cards[0].printCard();
    std::cout << " ";
    this->Hand.Cards[1].printCard();
    std::cout << std::endl;
}

//
// accessors
//
std::vector<Card> Player::getCards() {
    return {this->Hand.Cards[0], this->Hand.Cards[1]};
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