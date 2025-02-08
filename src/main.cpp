/*main.cpp*/

//
// William Brittian
// 2025
//

#include <iostream>
#include <vector>

#include "chars.h"
#include "functions.h"
#include "game.h"
#include "player.h"

using namespace std;

int main() {

  setColor("red");
  cout << "test1" << endl;
  setColor("black");
  cout << "test2" << endl;

  int NUM_BOTS = 3;
  int STARTING_CASH = 500;

  string name;
  Game game;

  printTitle();
  name = getName();

  Player *player = new Player(name, STARTING_CASH);
  game.initializeGame(player, NUM_BOTS, STARTING_CASH);

  //
  // main game loop
  //

}