/*game.cpp*/

//
// a poker game
//
// William Brittian
// 2025
//

#include "game.hpp"

void Game::initializeGame(const struct EngineSettings& settings, std::vector<int> PlayerIds) {
    this->Deck.refillCards();

    for (int id : PlayerIds) {
        struct Seat seat = {
            id,
            false,
            settings.StartingCash,
            0,
            0
        };

        this->Players.push_back(seat);
    }
}