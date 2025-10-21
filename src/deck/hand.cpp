/*hand.cpp*/

//
// enum for hand types
//
// William Brittian
// 2025
//

#include "hand.hpp"

int getHighCard(const uint16_t& mask) {
    return 15 - __builtin_clz(mask);
}

int checkStraight(const uint16_t &mask) {
    int straightHigh = -1;

    if ((mask & (1u << 12)) && ((mask & 0x000F) == 0x000F)) {
        straightHigh = 3;
    }

    uint32_t m = mask;
    uint32_t straight = m & (m<<1) & (m<<2) & (m<<3) & (m<<4);
    straight &= 0x1FFF;
    
    if (straight != 0) {
        straightHigh = 4 + getHighCard(straight);
    }

    return straightHigh;
}

std::vector<int> checkFlush(const uint16_t (&mask)[4]) {
    std::vector<int> flush;

    for (int i = 0; i < 4; i++) {
        if (__builtin_popcount(mask[i]) >= 5) {
            int offset = 0;
            if (checkStraight(mask[i]) != -1) {
                offset += 20;
            }

            uint16_t m = mask[i];
            for (int j = 0; j < 5; j++) {
                int rank = getHighCard(m);
                m = m - (1u << rank);

                flush.push_back(rank + offset);
            }
        }
    }

    if (flush.size() == 0) {
        return {-1};
    } else {

    }
}

void countTypes(const uint16_t (&mask)[4], std::map<int, int>& counts) {

}


void Hand::evaluateHand() {
    std::map<int, int> counts;
    uint16_t mask[4];

    for (Card card : Cards) {
        mask[card.Rank] |= 1u << card.Suit;
    }

    int straight = checkStraight(mask[0] | mask[1] | mask[2] | mask[3]);
    std::vector<int> flush = checkFlush(mask);
    countTypes(mask, counts);

    if (flush[0] >= 20) {
        flush -= 20;
        Type = STRAIGHT_FLUSH;

        if (flush == 12) {
            Type = ROYAL_FLUSH;
        }

        HandHigh.push_back(flush);
    } else if (flush >= 0) {
        Type = FLUSH;
        
    }
}