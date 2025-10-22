/*hand.cpp*/

//
// enum for hand types
//
// William Brittian
// 2025
//

#include "hand.hpp"

int getHighCard(const uint16_t& mask) {
    if (!mask) return -1;
    return 31 - __builtin_clz(mask);
}

std::vector<int> getNHighCards(uint16_t mask, const int& N, const int& offset = 0) {
    std::vector<int> ans;
    for (int i = 0; i < N; i++) {
        int rank = getHighCard(mask);
        mask &= ~(1u << rank);

        ans.push_back(rank + offset);
    }

    return ans;
}

std::vector<int> getNHighCards(
    std::map<int, int, std::greater<int>>& counts, 
    const int& N = 1
) {
    std::vector<int> ans;
    for (int i = 0; i < N; i++) {
        auto it = counts.begin();
        int rank = it->first;
        int& count = it->second;

        ans.push_back(rank);

        if (--count == 0) counts.erase(it);
    }

    return ans;
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
        straightHigh = getHighCard(straight);
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
            
            flush = getNHighCards(mask[i], 5, offset);
        }
    }

    if (flush.size() == 0) {
        return {-1};
    } else {
        return flush;
    }
}


void Hand::evaluateHand() {
    std::map<int, int, std::greater<int>> counts;
    uint16_t mask[4] = {0, 0, 0, 0};

    for (Card card : Cards) {
        mask[card.Suit] |= (1u << card.Rank);
        counts[card.Rank]++;
    }

    uint16_t rankMask = mask[0] | mask[1] | mask[2] | mask[3];

    std::vector<int> flush = checkFlush(mask);
    if (flush.size() > 1) {
        if (flush[0] >= 20) {
            for (int& c : flush)
                c -= 20;
            
            Type = STRAIGHT_FLUSH;

            if (flush[0] == 12) {
                Type = ROYAL_FLUSH;
            }
        } else {
            Type = FLUSH;
        }

        HandHigh = flush;
        return;
    } 
    
    int straight = checkStraight(rankMask);
    if (straight != -1) {
        Type = STRAIGHT;
        HandHigh = {straight};
        return;
    }

    // not straight or flush so count ranks
    int quads = -1;
    std::vector<int> trips, pairs;
    for (auto it = counts.begin(); it != counts.end(); ) {
        int rank = it->first;
        int count = it-> second;

        if (count == 4) {
            quads = rank;
            it = counts.erase(it);
            continue;
        } else if (count == 3) {
            trips.push_back(rank);
            it = counts.erase(it);
            continue;
        } else if (count == 2) {
            pairs.push_back(rank);
            it = counts.erase(it);
            continue;
        }
        ++it;
    }

    if (quads != -1) {
        Type = FOUR_OF_A_KIND;
        HandHigh = {quads};
        OtherHigh = getNHighCards(counts);
    } else if (trips.size() == 2 || trips.size() >= 1 && pairs.size() >= 1) {
        Type = FULL_HOUSE;
        HandHigh = {trips[0]};

        int trip = 0;
        int pair = 0;

        if (trips.size() == 2)
            trip = trips[1];
        if (!pairs.empty())
            pair = pairs[0];

        if (trip >= pair)
            OtherHigh = {trip};
        else
            OtherHigh = {pair};
    } else if (!trips.empty()) {
        Type = THREE_OF_A_KIND;
        HandHigh = {trips[0]};
        OtherHigh = getNHighCards(counts, 2);
    } else if (pairs.size() >= 2) {
        Type = TWO_PAIR;
        HandHigh = {pairs[0], pairs[1]};
        OtherHigh = getNHighCards(counts);
    } else if (!pairs.empty()) {
        Type = PAIR;
        HandHigh = {pairs[0]};
        OtherHigh = getNHighCards(counts, 3);
    } else {
        Type = HIGH_CARD;
        HandHigh = getNHighCards(counts, 5);
    }
}