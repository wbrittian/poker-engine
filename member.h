/*member.h*/

//
// a member of the table
//
// William Brittian
// 2025
//

#pragma once

#include "player.h"

struct Member {
    Player* player;
    Player* next;
    bool playing;
};