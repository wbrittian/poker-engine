/*game.cpp*/

//
// a poker game
//
// William Brittian
// 2025
//

#include "game.hpp"

//
// general game state functions
//

void Game::initializeGame(std::shared_ptr<Player> player, int numBots, int startingCash) {
    this->Deck.refillCards();

    this->User = player;
    this->addPlayer(player, nullptr);
    player->setNextPlayer(player);

    // add bots
    for (int i = 0; i < numBots; i++) {
        std::string name = "Bot " + std::to_string(numBots - i);

        this->addPlayer(std::make_shared<Bot>(name, startingCash), player);
    }
}

void Game::finishGame() {
    while (this->NumPlayers > 0) {
        removePlayer(this->Head);
    }
}

void Game::runRound() {
    this->Deck.refillCards();
    this->NumPlaying = this->NumPlayers;
    this->Round++;

    std::cout << "ROUND " << this->Round << std::endl;

    // TODO: implement main game loop
    while (this->Stage < 5 && !this->Quit) {
        std::cout << std::endl;
        this->printState();

        if (this->Stage == 0) {
            this->dealCards();

            std::cout << "You are dealt:" << std::endl;
            this->User->printCards();
            std::cout << std::endl;

            this->Bet = 10;
        } else if (this->Stage == 1) {
            this->Cards = this->Deck.drawCards(3);
        } else if (this->Stage == 2) {
            this->Cards.push_back(this->Deck.drawCard());
        } else if (this->Stage == 3) {
            this->Cards.push_back(this->Deck.drawCard());
        } else if (this->Stage == 4) {
            this->settleRound();
            break;
        }

        this->runBetting();
        this->Stage++;

        this->printCards();
        this->printPot();

        while (!this->Quit) {
            std::string cmd;
            std::cout << "Enter a command (h for help) > ";
            std::cin >> cmd;
            std::cout << std::endl;

            if (cmd == "q") {
                this->Quit = true;
                break;
            } else if (cmd == "h") {
                std::cout << "Available round active commands:" << std::endl
                          << "h -> get list of available commands" << std::endl
                          << "q -> quit the game" << std::endl
                          << "c -> continue round" << std::endl
                          << "s -> print scoreboard" << std::endl;
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

void Game::addPlayer(std::shared_ptr<Player> player, std::shared_ptr<Player> position) {
    if (position == nullptr) {
        this->Head = player;
    } else {
        std::shared_ptr<Player> temp = position->getNextPlayer();
        position->setNextPlayer(player);
        player->setNextPlayer(temp);
    }

    this->NumPlayers++;
}

void Game::removePlayer(std::shared_ptr<Player> player) {
    // TODO: what happens to user (and game) if you
    // remove the player? When will this get called
    // and will that happen?

    if (player->getNextPlayer() != player) {
        if (this->Head == player) {
            this->Head = player->getNextPlayer();
        }

        std::shared_ptr<Player> previous = this->getPreviousPlayer(player);
        std::shared_ptr<Player> next = player->getNextPlayer();

        previous->setNextPlayer(next);
    } else {
        this->Head = nullptr;
        this->User = nullptr;
    }

    this->NumPlayers--;
}

// rotates the head pointer to the next in the order
// head by default points to the small blind
void Game::rotateOrder() {
    this->Head = this->Head->getNextPlayer();
}

//
// round active functions
//

void Game::runGame() {
    while (!this->Quit) {
        if (this->Quit) {
            break;
        }

        std::cout << std::endl;
        this->printState();

        std::string cmd;
        std::cout << "Enter a command (h for help) > ";
        std::cin >> cmd;
        std::cout << std::endl;

        if (cmd == "q") {
            this->Quit = true;
        } else if (cmd == "h") {
            std::cout << "Available preround commands:" << std::endl
                      << "h -> get a list of available commands" << std::endl
                      << "q -> quit the game" << std::endl
                      << "r -> start a new round" << std::endl
                      << "s -> print game scoreboard" << std::endl;
        } else if (cmd == "r") {
            this->Active = true;
            this->runRound();
        } else if (cmd == "s") {
            this->printScoreboard();
        } else if (cmd == "p") {
            std::cout << this->NumPlayers << std::endl;
        } else {
            std::cout << "Unknown comand" << std::endl;
        }
    }
}

void Game::runBetting() {
    std::shared_ptr<Player> raiser = this->Head;
    std::shared_ptr<Player> current = this->Head;

    do {
        Action action;

        if (current == this->User) {
            this->printRoundInfo();

            action = {NONE, 0};
            while (action.Type == NONE && !this->Quit) {
                std::string cmd;
                std::cout << "Enter your action, type h for help > ";
                std::cin >> cmd;
                std::cout << std::endl;

                if (cmd == "q") {
                    this->Quit = true;
                } else if (cmd == "h") {
                    std::cout << "Available round active commands:" << std::endl
                              << "h -> get list of available commands" << std::endl
                              << "q -> quit the game" << std::endl
                              << "c -> call the current bet or check" << std::endl
                              << "b/r [AMOUNT] -> bet (or raise) the given amount" << std::endl
                              << "f -> fold your hand" << std::endl
                              << "s -> print scoreboard" << std::endl;
                } else if (cmd == "s") {
                    this->printScoreboard();
                } else {
                    action = this->User->getAction(cmd, this->Bet);
                }
            }

        } else {
            auto bot = std::dynamic_pointer_cast<Bot>(current);
            action = bot->getAction(
                this->Bet, this->Pot, this->NumPlayers); // IMPORTANT: FIX POLYMORPHISM FOR BOTS
        }

        // shouldn't be possible, but want to make sure
        if (action.Type == NONE) {
            continue;
        } else if (action.Type == BET) {
            int totalBet = this->Bet + action.Amount;
            this->settleBet(totalBet, current);

            raiser = current;
        } else if (action.Type == FOLD) {
        }

        current = current->getNextPlayer();
    } while (current != raiser && !this->Quit);

    std::cout << std::endl;
    this->clearAllBets();
}

void Game::dealToPlayer(std::shared_ptr<Player> player) {
    player->resetHand();
    player->addCards(this->Deck.drawCards(2));
}

void Game::dealCards() {
    std::shared_ptr<Player> cur = this->Head;
    do {
        this->dealToPlayer(cur);
        cur = cur->getNextPlayer();
    } while (cur != this->Head);
}

void Game::settleBet(int amount, std::shared_ptr<Player> player) {
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

    std::shared_ptr<Player> current = this->Head;
    do {
        current->resetBet();
        current = current->getNextPlayer();
    } while (current != this->Head);
}

void Game::printState() {
    if (this->Active) {
        setColor("green");
        std::cout << "<<Round Active>>" << std::endl;
    } else {
        setColor("red");
        std::cout << "<<Round Inactive>>" << std::endl;
    }
    setColor("black");
}

void Game::printScoreboard() {
    std::shared_ptr<Player> cur = this->User;
    do {
        std::cout << cur->getName() << ": " << cur->getCash() << std::endl;
        cur = cur->getNextPlayer();
    } while (cur != this->User);
    std::cout << std::endl;
}

//
// misc
//

// 0-indexed
std::shared_ptr<Player> Game::getNthPlayer(int n) {
    std::shared_ptr<Player> cur = this->Head;
    while (n > 0) {
        cur = cur->getNextPlayer();
    }

    return cur;
}

// returns the player behind the given player in the order
std::shared_ptr<Player> Game::getPreviousPlayer(std::shared_ptr<Player> player) {
    std::shared_ptr<Player> current = player;

    while (current->getNextPlayer() != player) {
        current = current->getNextPlayer();
    }

    return current;
}

void Game::printCards() {
    if (this->Cards.size() > 0) {
        for (Card card : this->Cards) {
            card.printCard();
            std::cout << " ";
        }
    } else {
        std::cout << "no community cards";
    }
    std::cout << std::endl;
}

void Game::printRoundInfo() {
    if (this->Stage > 0) {
        std::cout << "Community cards:" << std::endl;
        this->printCards();
        std::cout << std::endl;
    }

    
    std::cout << "Your cards:" << std::endl;
    this->User->printCards();
    std::cout << std::endl;

    std::cout << "Pot (your share): " << this->Pot << " (" << this->User->getPotSplit() << ")"
        << std::endl;

    std::cout << "Current Bet: " << this->Bet << std::endl;
    std::cout << "To play: " << this->Bet - this->User->getBet() << std::endl;
}

void Game::printPot() {
    std::cout << "Pot: " << this->Pot << std::endl << std::endl;
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

std::shared_ptr<Player> Game::getHead() {
    return this->Head;
}