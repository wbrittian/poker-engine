/*functions.h*/

//
// helper functions for running game
//
// William Brittian
// 2025
//

#pragma once

#include <iostream>
#include <sstream>
#include <string>

#include "chars.hpp"

std::string getName();

void printTitle();

void setColor(std::string color);

bool isInteger(const std::string& str);