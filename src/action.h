/*action.h*/

//
// a player's current choice of action
//
// William Brittian
// 2025
//

#pragma once

enum ActionTypes {
    CALL, // used for check and call
    RAISE, // used for bet and raise
    NONE // placeholder for no action
};

struct Action {
    enum ActionTypes Type = NONE;
    int Amount = 0;
};