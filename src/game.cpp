/*game.cpp*/

//
// a poker game
//
// William Brittian
// 2025
//

#include "game.h"

//
// general game state functions
//

void Game::initializeGame(Player *player, int numBots, int startingCash) {
    this->Deck.refillCards();

    this->User = player;
    this->addPlayer(player, nullptr);
    player->setNextPlayer(player);

    // add bots
    for (int i = 0; i < numBots; i++) {
        string name = "Bot " + to_string(numBots - i);

        this->addPlayer(new Bot(name, startingCash), player);
    }
}

void Game::finishGame() {

    while (this->NumPlayers > 0) {
        removePlayer(this->FirstPlayer);
    }
}

void Game::newRound() {
    this->Deck.refillCards();

    // TODO: implement main game loop
}

void Game::settleRound() {
    // TODO: implement code for determining winner

    this->Bet = 0;
    this->Pot = 0;
}

void Game::addPlayer(Player *player, Player *position) {
    if (position == nullptr) {
        this->FirstPlayer = player;
    } else {
        Player *temp = position->getNextPlayer();
        position->setNextPlayer(player);
        player->setNextPlayer(temp);
    }

    this->NumPlayers++;
}

void Game::removePlayer(Player *player) {

    // TODO: what happens to user (and game) if you
    // remove the player? When will this get called
    // and will that happen?

    if (player->getNextPlayer() != player) {
        if (this->FirstPlayer == player) {
            this->FirstPlayer = player->getNextPlayer();
        }

        Player *previous = this->getPreviousPlayer(player);
        Player *next = player->getNextPlayer();

        previous->setNextPlayer(next);
    } else {
        this->FirstPlayer = nullptr;
        this->User = nullptr;
    }

    this->NumPlayers--;
    delete player;
}

// rotates the head pointer to the next in the order
// head by default points to the small blind
void Game::rotateOrder() {
    this->FirstPlayer = this->FirstPlayer->getNextPlayer();
}

//
// round active functions
//

void Game::runGame() {

}

void Game::runBetting() {
    Player* raiser = this->FirstPlayer;
    Player* current = this->FirstPlayer;

    bool done = false;

    do {
        Action action;

        if (current == this->User) {
            this->printRoundInfo();
            action = this->User->getAction(this->Bet);
        } else {
            action = current->getAction(this->Bet); // IMPORTANT: FIX POLYMORPHISM FOR BOTS
        }

        // shouldn't be possible, but want to make sure
        if (action.Type == NONE) {
            continue;
        } else if (action.Type == CALL) {
            int settleAmount = this->Bet - current->getBet();
            this->settlePlayerPot(settleAmount, current);
        } else if (action.Type == BET) {
            int totalBet = this->Bet + action.Amount;
            this->settleBet(totalBet, current);

            raiser = current;
        } else if (action.Type == FOLD) {

        }

        if (current->getNextPlayer() == raiser) {
            done = true;
        }
    } while (current->getNextPlayer() != raiser);

    this->clearAllBets();
}

void Game::settlePlayerPot(int amount, Player *player) {
    if (this->Pot + amount < 0 || player->getCash() - amount < 0) {
        throw range_error("Negative value error");
    }

    player->editCash(-amount);
    this->Pot += amount;
}

void Game::settleBet(int amount, Player* player) {
    // amount needed to play - current betted
    int owed = amount - player->getBet();

    this->Bet = amount;
    this->Pot += owed;

    player->setBet(amount);
    player->editPotSplit(owed);
    player->editCash(-owed);
}

void Game::clearAllBets() {
    this->Bet = 0;

    Player* current = this->FirstPlayer;
    while (current->getNextPlayer() != this->FirstPlayer) {
        current->resetBet();
    }
}

void Game::dealToPlayer(Player *player) {
    player->emptyHand();
    player->addCards(this->Deck.drawCards(2));
}

//
// misc
//
Player *Game::getNthPlayer(int N) {

}

// returns the player behind the given player in the order
Player *Game::getPreviousPlayer(Player *player) {
    Player *current = player;

    while (current->getNextPlayer() != player) {
        current = current->getNextPlayer();
    }

    return current;
}

void Game::printCards() {
    for (Card card : this->Cards) {
        card.printCard(true);
        cout << " ";
    }
    cout << endl;
}

void Game::printRoundInfo() {
    if (this->Stage > 1) {
        cout << "Community cards:" << endl;
        this->printCards();
        cout << endl;
    } 
    
    if (this->Stage > 0) {
        cout << "Your cards:" << endl;
        this->User->printCards();
        cout << endl;

        cout << "Pot (your share): " << this->Pot <<  " (" << this->User->getPotSplit() << ")" << endl;
    }

    cout << "Current Bet: " << this->Bet << endl;
    cout << "To play: " << this->Bet - this->User->getBet() << endl;
}

//
// accessors
//
int Game::getPot() {
    return this->Pot; 
}

int Game::getBet() {
    return this->Bet;
}

int Game::getNumPlayers() {
    return this->NumPlayers;
}

Player *Game::getFirstPlayer() {
    return this->FirstPlayer;
}

// returns the player with the most cash
Player *Game::getCurrentLeader() {
    Player *leader = this->FirstPlayer;
    Player *current = this->FirstPlayer->getNextPlayer();

    while (current != this->FirstPlayer) {
        if (current->getCash() > leader->getCash()) {
            leader = current;
        }

        current = current->getNextPlayer();
    }

    return leader;
}