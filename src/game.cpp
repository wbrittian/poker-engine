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

        this->addPlayer(make_shared<Bot>(name, startingCash), player);
    }

    // start main game loop
    this->runGame();
}

void Game::finishGame() {
    while (this->NumPlayers > 0) {
        removePlayer(this->FirstPlayer);
    }
}

void Game::runRound() {
    this->Deck.refillCards();
    this->NumPlaying = this->NumPlayers;
    this->Round++;

    cout << "ROUND " << this->Round << endl;

    // TODO: implement main game loop
    while (this->Stage < 5 && !this->Quit) {
        cout << endl;
        this->printState();

        if (this->Stage == 0) {
            this->dealCards();

            cout << "You are dealt:" << endl;
            this->User->printCards();
            cout << endl;

            this->Bet = 10;
        } else if (this->Stage == 1) {
            cout << "hi" << endl;
        }

        this->runBetting();
        this->Stage++;

        this->printCards();
        this->printPot();

        while (!this->Quit) {
            string cmd;
            cout << "Enter a command (h for help) > ";
            cin >> cmd;
            cout << endl;

            if (cmd == "q") {
                this->Quit = true;
                break;
            } else if (cmd == "h") {
                cout << "Available round active commands:" << endl
                     << "h -> get list of available commands" << endl
                     << "q -> quit the game" << endl
                     << "c -> continue round" << endl
                     << "s -> print scoreboard" << endl;
            } else if (cmd == "c") {
                break;
            } else if (cmd == "s") {
                this->printScoreboard();
            }
        }
    }
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
    while (!this->Quit) {
        if (this->Quit) {
            break;
        }

        cout << endl;
        this->printState();

        string cmd;
        cout << "Enter a command (h for help) > ";
        cin >> cmd;
        cout << endl;

        if (cmd == "q") {
            this->Quit = true;
        } else if (cmd == "h") {
            cout << "Available preround commands:" << endl
                 << "h -> get a list of available commands" << endl
                 << "q -> quit the game" << endl
                 << "r -> start a new round" << endl
                 << "s -> print game scoreboard" << endl;
        } else if (cmd == "r") {
            this->Active = true;
            this->runRound();
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

    do {
        Action action;

        if (current == this->User) {
            this->printRoundInfo();

            action = {NONE, 0};
            while (action.Type == NONE && !this->Quit) {
                string cmd;
                cout << "Enter your action, type h for help > ";
                cin >> cmd;
                cout << endl;

                if (cmd == "q") {
                    this->Quit = true;
                } else if (cmd == "h") {
                    cout << "Available round active commands:" << endl
                         << "h -> get list of available commands" << endl
                         << "q -> quit the game" << endl
                         << "c -> call the current bet or check" << endl
                         << "b/r [AMOUNT] -> bet (or raise) the given amount" << endl
                         << "f -> fold your hand" << endl
                         << "s -> print scoreboard" << endl;
                } else if (cmd == "s") {
                    this->printScoreboard();
                } else {
                    action = this->User->getAction(cmd, this->Bet);
                }
            }

        } else {
            auto bot = dynamic_pointer_cast<Bot>(current);
            action = bot->getAction(
                this->Bet, this->Pot, this->NumPlayers); // IMPORTANT: FIX POLYMORPHISM FOR BOTS
        }

        // shouldn't be possible, but want to make sure
        if (action.Type == NONE) {
            continue;
        } else if (action.Type == CALL) {
            this->settleBet(this->Bet, current);
        } else if (action.Type == BET) {
            int totalBet = this->Bet + action.Amount;
            this->settleBet(totalBet, current);

            raiser = current;
        } else if (action.Type == FOLD) {
        }

        current = current->getNextPlayer();
    } while (current != raiser && !this->Quit);

    cout << endl;
    this->clearAllBets();
}

void Game::dealToPlayer(shared_ptr<Player> player) {
    player->emptyHand();
    player->addCards(this->Deck.drawCards(2));
}

void Game::dealCards() {
    shared_ptr<Player> cur = this->FirstPlayer;
    do {
        this->dealToPlayer(cur);
        cur = cur->getNextPlayer();
    } while (cur != this->FirstPlayer);
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
    do {
        current->resetBet();
        current = current->getNextPlayer();
    } while (current != this->FirstPlayer);
}

void Game::printState() {
    if (this->Active) {
        setColor("green");
        cout << "<<Round Active>>" << endl;
    } else {
        setColor("red");
        cout << "<<Round Inactive>>" << endl;
    }
    setColor("black");
}

void Game::printScoreboard() {
    shared_ptr<Player> cur = this->User;
    do {
        cout << cur->getName() << ": " << cur->getCash() << endl;
        cur = cur->getNextPlayer();
    } while (cur != this->User);
    cout << endl;
}

//
// misc
//

// 0-indexed
shared_ptr<Player> Game::getNthPlayer(int n) {
    shared_ptr<Player> cur = this->FirstPlayer;
    while (n > 0) {
        cur = cur->getNextPlayer();
    }

    return cur;
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
    if (this->Cards.size() > 0) {
        for (Card card : this->Cards) {
            card.printCard(true);
            cout << " ";
        }
    } else {
        cout << "no community cards";
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

        cout << "Pot (your share): " << this->Pot << " (" << this->User->getPotSplit() << ")"
             << endl;
    }

    cout << "Current Bet: " << this->Bet << endl;
    cout << "To play: " << this->Bet - this->User->getBet() << endl;
}

void Game::printPot() {
    cout << "Pot: " << this->Pot << endl << endl;
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