/*main.cpp*/

//
// William Brittian
// 2025
//

#include <iostream>
#include <vector>

#include "game.h"
#include "player.h"
#include "deck.h"
#include "bot.h"

using namespace std;

int main() {

    int NUM_BOTS = 3;
    int STARTING_CASH = 500;

    string name;
    Game game;

    cout << endl;
    cout << "***********************" << endl;
    cout << "   Welcome to Poker!   " << endl;
    cout << endl;
    cout << " William Brittian 2025 " << endl;
    cout << "***********************" << endl;
    cout << endl;

    cout << "please enter your name:" << endl;
    getline(cin, name);
    cout << endl;

    Player* player = new Player(name, STARTING_CASH);
    game.initializeGame(player, NUM_BOTS, STARTING_CASH);


    //
    // main game loop
    //


}