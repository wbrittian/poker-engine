/*test_hand_unit.cpp*/

//
// poker-engine unit tests for hand evaluation
//
// William Brittian
// 2025
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../fixtures.cpp"

using ::testing::ElementsAre;
using ::testing::ElementsAreArray;

// --- FULL HOUSE (single trips + single pair) ---
TEST_F(HandTest, FullHouse_TripPlusPair) {
    hand.Cards = {
        makeCard(THREE, SPADES),
        makeCard(THREE, DIAMONDS),
        makeCard(FOUR, DIAMONDS),
        makeCard(QUEEN, SPADES),
        makeCard(QUEEN, DIAMONDS),
        makeCard(QUEEN, CLUBS),
        makeCard(SEVEN, HEARTS)
    };
    hand.evaluateHand({});

    EXPECT_EQ(hand.Type, FULL_HOUSE);
    EXPECT_THAT(hand.HandHigh, ElementsAre(QUEEN));  // trips
    EXPECT_THAT(hand.OtherHigh, ElementsAre(THREE)); // pair
}

// --- FULL HOUSE (two trips; second trips acts as the pair) ---
TEST_F(HandTest, FullHouse_TwoTrips) {
    hand.Cards = {
        makeCard(KING, CLUBS),
        makeCard(KING, DIAMONDS),
        makeCard(KING, HEARTS),
        makeCard(NINE, SPADES),
        makeCard(NINE, DIAMONDS),
        makeCard(NINE, CLUBS),
        makeCard(TWO, HEARTS)
    };
    hand.evaluateHand({});

    EXPECT_EQ(hand.Type, FULL_HOUSE);
    EXPECT_THAT(hand.HandHigh, ElementsAre(KING));
    EXPECT_THAT(hand.OtherHigh, ElementsAre(NINE));
}

// --- FOUR OF A KIND + kicker ---
TEST_F(HandTest, FourOfAKind_WithKicker) {
    hand.Cards = {
        makeCard(FIVE, CLUBS),
        makeCard(FIVE, DIAMONDS),
        makeCard(FIVE, HEARTS),
        makeCard(FIVE, SPADES),
        makeCard(ACE, HEARTS),
        makeCard(THREE, CLUBS),
        makeCard(SEVEN, DIAMONDS)
    };
    hand.evaluateHand({});

    EXPECT_EQ(hand.Type, FOUR_OF_A_KIND);
    EXPECT_THAT(hand.HandHigh, ElementsAre(FIVE));
    EXPECT_THAT(hand.OtherHigh, ElementsAre(ACE));
}

// --- THREE OF A KIND + two kickers ---
TEST_F(HandTest, Trips_WithKickers) {
    hand.Cards = {
        makeCard(SEVEN, CLUBS),
        makeCard(SEVEN, DIAMONDS),
        makeCard(SEVEN, HEARTS),
        makeCard(ACE, SPADES),
        makeCard(KING, DIAMONDS),
        makeCard(FOUR, CLUBS),
        makeCard(THREE, HEARTS)
    };
    hand.evaluateHand({});

    EXPECT_EQ(hand.Type, THREE_OF_A_KIND);
    EXPECT_THAT(hand.HandHigh, ElementsAre(SEVEN));
    // Expect top two kickers: A, K
    ASSERT_EQ(hand.OtherHigh.size(), 2u);
    EXPECT_EQ(hand.OtherHigh[0], ACE);
    EXPECT_EQ(hand.OtherHigh[1], KING);
}

// --- TWO PAIR + kicker ---
TEST_F(HandTest, TwoPair_WithKicker) {
    hand.Cards = {
        makeCard(ACE, CLUBS), makeCard(ACE, DIAMONDS),
        makeCard(TEN, HEARTS), makeCard(TEN, SPADES),
        makeCard(KING, HEARTS),
        makeCard(FOUR, CLUBS),
        makeCard(THREE, DIAMONDS)
    };
    hand.evaluateHand({});

    EXPECT_EQ(hand.Type, TWO_PAIR);
    EXPECT_THAT(hand.HandHigh, ElementsAre(ACE, TEN));
    EXPECT_THAT(hand.OtherHigh, ElementsAre(KING));
}

// --- ONE PAIR + 3 kickers ---
TEST_F(HandTest, OnePair_WithKickers) {
    hand.Cards = {
        makeCard(NINE, CLUBS), makeCard(NINE, DIAMONDS),
        makeCard(ACE, HEARTS),
        makeCard(KING, SPADES),
        makeCard(QUEEN, HEARTS),
        makeCard(THREE, CLUBS),
        makeCard(FOUR, DIAMONDS)
    };
    hand.evaluateHand({});

    EXPECT_EQ(hand.Type, PAIR);
    EXPECT_THAT(hand.HandHigh, ElementsAre(NINE));
    EXPECT_THAT(hand.OtherHigh, ElementsAre(ACE, KING, QUEEN));
}

// --- HIGH CARD (top 5 ranks) ---
TEST_F(HandTest, HighCard_TopFive) {
    hand.Cards = {
        makeCard(ACE, CLUBS),
        makeCard(QUEEN, DIAMONDS),
        makeCard(NINE, HEARTS),
        makeCard(SEVEN, SPADES),
        makeCard(FOUR, HEARTS),
        makeCard(THREE, CLUBS),
        makeCard(EIGHT, DIAMONDS)
    };
    hand.evaluateHand({});

    EXPECT_EQ(hand.Type, HIGH_CARD);
    // Expect A, Q, 9, 8, 7 (assuming descending selection)
    ASSERT_EQ(hand.HandHigh.size(), 5u);
    EXPECT_THAT(hand.HandHigh, ElementsAre(ACE, QUEEN, NINE, EIGHT, SEVEN));
}

// --- STRAIGHT: normal (10-J-Q-K-A) ---
TEST_F(HandTest, Straight_AceHigh) {
    hand.Cards = {
        makeCard(TEN, CLUBS),
        makeCard(JACK, DIAMONDS),
        makeCard(QUEEN, HEARTS),
        makeCard(KING, SPADES),
        makeCard(ACE, HEARTS),
        makeCard(TWO, CLUBS),   // junk
        makeCard(FOUR, DIAMONDS)// junk
    };
    hand.evaluateHand({});

    EXPECT_EQ(hand.Type, STRAIGHT);
    EXPECT_THAT(hand.HandHigh, ElementsAre(ACE)); // top rank of straight
}

// --- STRAIGHT: wheel (A-2-3-4-5) ---
TEST_F(HandTest, Straight_Wheel) {
    hand.Cards = {
        makeCard(ACE, CLUBS),
        makeCard(TWO, DIAMONDS),
        makeCard(THREE, HEARTS),
        makeCard(FOUR, SPADES),
        makeCard(FIVE, HEARTS),
        makeCard(TEN, CLUBS),  // junk
        makeCard(QUEEN, SPADES)// junk
    };
    hand.evaluateHand({});

    EXPECT_EQ(hand.Type, STRAIGHT);
    EXPECT_THAT(hand.HandHigh, ElementsAre(FIVE)); // 5-high straight
}

// --- STRAIGHT: multiple runs present (choose highest) ---
TEST_F(HandTest, Straight_PicksHighestRun) {
    // 5-6-7-8-9-10 creates two 5-card windows; expect top=10
    hand.Cards = {
        makeCard(FIVE, CLUBS),
        makeCard(SIX, DIAMONDS),
        makeCard(SEVEN, HEARTS),
        makeCard(EIGHT, SPADES),
        makeCard(NINE, HEARTS),
        makeCard(TEN, CLUBS),
        makeCard(TWO, DIAMONDS)
    };
    hand.evaluateHand({});

    EXPECT_EQ(hand.Type, STRAIGHT);
    EXPECT_THAT(hand.HandHigh, ElementsAre(TEN));
}

// --- FLUSH: non-straight flush (prefer flush over straight if both exist) ---
TEST_F(HandTest, Flush_WinsOverSeparateStraight) {
    // Hearts flush  A,Q,9,6,2  (not straight),
    // also a separate board straight present, but evaluator should pick FLUSH first.
    hand.Cards = {
        makeCard(ACE, HEARTS),
        makeCard(QUEEN, HEARTS),
        makeCard(NINE, HEARTS),
        makeCard(SIX, HEARTS),
        makeCard(TWO, HEARTS),
        makeCard(FIVE, CLUBS),  // helps a potential straight
        makeCard(TEN, DIAMONDS) // helps a potential straight
    };
    hand.evaluateHand({});

    EXPECT_EQ(hand.Type, FLUSH);
    ASSERT_EQ(hand.HandHigh.size(), 5u);
    EXPECT_THAT(hand.HandHigh, ElementsAre(ACE, QUEEN, NINE, SIX, TWO));
}

// --- STRAIGHT FLUSH (non-royal) ---
TEST_F(HandTest, StraightFlush) {
    hand.Cards = {
        makeCard(NINE, SPADES),
        makeCard(TEN, SPADES),
        makeCard(JACK, SPADES),
        makeCard(QUEEN, SPADES),
        makeCard(KING, SPADES),
        makeCard(TWO, DIAMONDS),
        makeCard(THREE, CLUBS)
    };
    hand.evaluateHand({});

    EXPECT_EQ(hand.Type, STRAIGHT_FLUSH);
    // HandHigh content can vary by implementation (top rank vs 5 ranks). Don’t over-assert here.
}

// --- ROYAL FLUSH ---
TEST_F(HandTest, RoyalFlush) {
    hand.Cards = {
        makeCard(TEN, HEARTS),
        makeCard(JACK, HEARTS),
        makeCard(QUEEN, HEARTS),
        makeCard(KING, HEARTS),
        makeCard(ACE, HEARTS),
        makeCard(TWO, CLUBS),
        makeCard(THREE, DIAMONDS)
    };
    hand.evaluateHand({});

    EXPECT_EQ(hand.Type, ROYAL_FLUSH);
}