/*functions.h*/

//
// helper functions for running game
//
// William Brittian
// 2025
//

#pragma once

#include <iostream>
#include <string>
#include <sstream>

#include "chars.h"

using namespace std;

string getName();

void printTitle();

void setColor(string color);

bool isInteger(const string& str);