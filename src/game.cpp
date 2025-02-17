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

void Game::initializeGame(shared_ptr<Player> player, int numBots, int startingCash) {
    this->Deck.refillCards();

    this->User = player;
    this->addPlayer(player, nullptr);
    player->setNextPlayer(player);

    // add bots
    for (int i = 0; i < numBots; i++) {
        string name = "Bot " + to_string(numBots - i);

        this->addPlayer(make_shared<Player>(name, startingCash), player);
    }

    // start main game loop
    this->runGame();
}

void Game::finishGame() {

    while (this->NumPlayers > 0) {
        removePlayer(this->FirstPlayer);
    }
}

void Game::startRound() {
    this->Deck.refillCards();

    // TODO: implement main game loop
}

void Game::settleRound() {
    // TODO: implement code for determining winner

    this->Bet = 0;
    this->Pot = 0;
}

void Game::addPlayer(shared_ptr<Player> player, shared_ptr<Player> position) {
    if (position == nullptr) {
        this->FirstPlayer = player;
    } else {
        shared_ptr<Player> temp = position->getNextPlayer();
        position->setNextPlayer(player);
        player->setNextPlayer(temp);
    }

    this->NumPlayers++;
}

void Game::removePlayer(shared_ptr<Player> player) {

    // TODO: what happens to user (and game) if you
    // remove the player? When will this get called
    // and will that happen?

    if (player->getNextPlayer() != player) {
        if (this->FirstPlayer == player) {
            this->FirstPlayer = player->getNextPlayer();
        }

        shared_ptr<Player> previous = this->getPreviousPlayer(player);
        shared_ptr<Player> next = player->getNextPlayer();

        previous->setNextPlayer(next);
    } else {
        this->FirstPlayer = nullptr;
        this->User = nullptr;
    }

    this->NumPlayers--;
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

    while (true) {
        cout << endl;
        this->printState();

        string cmd;
        cout << "Enter a command (h for help) > ";
        cin >> cmd;
        cout << endl;

        if (cmd == "q") {
            break;
        } else if (cmd == "h") {
            cout << "Available preround commands:"
            << endl << "h -> get a list of available commands"
            << endl << "q -> quit the game"
            << endl << "r -> start a new round"
            << endl << "s -> print game scoreboard"
            << endl;
        } else if (cmd == "r") {
            this->startRound();
        } else if (cmd == "s") {
            this->printScoreboard();
        } else if (cmd == "p") {
            cout << this->NumPlayers << endl;
        } else {
            cout << "Unknown comand" << endl;
        }
    }
}

void Game::runBetting() {
    shared_ptr<Player> raiser = this->FirstPlayer;
    shared_ptr<Player> current = this->FirstPlayer;

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

void Game::settlePlayerPot(int amount, shared_ptr<Player> player) {
    if (this->Pot + amount < 0 || player->getCash() - amount < 0) {
        throw range_error("Negative value error");
    }

    player->editCash(-amount);
    this->Pot += amount;
}

void Game::settleBet(int amount, shared_ptr<Player> player) {
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

    shared_ptr<Player> current = this->FirstPlayer;
    while (current->getNextPlayer() != this->FirstPlayer) {
        current->resetBet();
    }
}

void Game::dealToPlayer(shared_ptr<Player> player) {
    player->emptyHand();
    player->addCards(this->Deck.drawCards(2));
}

void Game::printState() {
    if (this->Active) {
        cout << "<<Round Active>>" << endl;
    } else {
        cout << "<<Round Inactive>>" << endl;
    }
}

void Game::printScoreboard() {
    shared_ptr<Player> cur = this->User;
    do {
        cout << cur->getName() << ": " << cur->getCash() << endl;
        cur = cur->getNextPlayer();
    } while (cur != this->User);
}

//
// misc
//
shared_ptr<Player> Game::getNthPlayer(int N) {
    
}

// returns the player behind the given player in the order
shared_ptr<Player> Game::getPreviousPlayer(shared_ptr<Player> player) {
    shared_ptr<Player> current = player;

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

shared_ptr<Player> Game::getFirstPlayer() {
    return this->FirstPlayer;
}

// returns the player with the most cash
shared_ptr<Player> Game::getCurrentLeader() {
    shared_ptr<Player> leader = this->FirstPlayer;
    shared_ptr<Player> current = this->FirstPlayer->getNextPlayer();

    while (current != this->FirstPlayer) {
        if (current->getCash() > leader->getCash()) {
            leader = current;
        }

        current = current->getNextPlayer();
    }

    return leader;
}