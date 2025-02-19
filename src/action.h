/*action.h*/

//
// a player's current choice of action
//
// William Brittian
// 2025
//

#pragma once

enum ActionTypes {
    NONE = 0, // placeholder for no action
    CALL, // used for check and call
    BET, // used for bet and raise
    FOLD // fold hand
};

struct Action {
    enum ActionTypes Type = NONE;
    int Amount = 0;
};