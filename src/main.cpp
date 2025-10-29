/*main.cpp*/

//
// William Brittian
// 2025
//

#include <iostream>
#include <vector>

#include "cli/cli.hpp"
#include "core/engine.hpp"


int main() {
    int NUM_PLAYERS = 6;

    CLI cli;
    PokerEngine engine;

    EngineSettings settings = cli.startup(NUM_PLAYERS);

    engine.initializeEngine(settings, NUM_PLAYERS);
    // cli.runGame(engine);

    std::vector<Seat> players;
    for (int i = 0; i < 6; i++) {
        players.push_back(Seat{
            i,
            true,
            1000,
            0,
            0
        });
    }


    PublicState test = {
        1,
        players,
        PREFLOP,
        0,
        0,
        0,
        0,
        {Card{ACE, SPADES}, Card{TWO, DIAMONDS}, Card{KING, CLUBS}}
    };

    PlayerState ptest = {
        std::vector{Card{JACK, HEARTS}, Card{ACE, CLUBS}}
    };

    cli.printState(test, ptest);
}