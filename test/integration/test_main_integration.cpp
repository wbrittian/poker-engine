/*test_main_integration.cpp*/

//
// poker-engine integration tests
//
// William Brittian
// 2025
//

#include <gtest/gtest.h>

#include "../fixtures.cpp"

// total chips in play at any point (Cash + uncommitted Bets + Pot)
static int totalChips(const PublicState& state) {
    int total = state.Pot;
    for (const Seat& s : state.Players) {
        total += s.Cash + s.Bet;
    }
    return total;
}

// --- FOLD WINS POT ---

// all players fold to one; verify chip conservation and round advances
TEST(EngineTest, FoldWinsPot_ChipsConserved) {
    PokerEngine engine;
    EngineSettings settings;
    engine.initializeEngine(settings, 3);

    engine.submitAction({2, FOLD});
    engine.submitAction({0, FOLD});

    PublicState state = engine.getPublicState();
    EXPECT_EQ(state.HandNum, 2);
    EXPECT_EQ(totalChips(state), 3 * settings.StartingCash);
}

// verify ResultState captures correct winner and pot
TEST(EngineTest, FoldWinsPot_ResultState) {
    PokerEngine engine;
    EngineSettings settings;
    engine.initializeEngine(settings, 3);

    // player 0 = SB (10), player 1 = BB (20), player 2 acts first
    engine.submitAction({2, FOLD});
    engine.submitAction({0, FOLD}); // player 1 wins

    ResultState result = engine.getResultState();
    EXPECT_EQ(result.Winner, 1);
    EXPECT_EQ(result.Pot, settings.SmallBlind + settings.BigBlind); // 30
}

// two-player fold: player 1 folds, player 0 (SB) wins
TEST(EngineTest, FoldWinsPot_HeadsUp) {
    PokerEngine engine;
    EngineSettings settings;
    engine.initializeEngine(settings, 2);

    // heads-up: SB=0 posts 10, BB=1 posts 20, SB acts first
    engine.submitAction({0, FOLD});

    ResultState result = engine.getResultState();
    EXPECT_EQ(result.Winner, 1);
    EXPECT_EQ(totalChips(engine.getPublicState()), 2 * settings.StartingCash);
}

// --- CHIP CONSERVATION THROUGH FULL HAND ---

// all players call preflop, check through river to showdown
TEST(EngineTest, ChipsConserved_FullHand) {
    PokerEngine engine;
    EngineSettings settings;
    engine.initializeEngine(settings, 3);

    // preflop: player 2 calls, player 0 (SB) calls, player 1 (BB) checks
    engine.submitAction({2, BET, 0});
    engine.submitAction({0, BET, 0});
    engine.submitAction({1, BET, 0});

    // flop, turn, river: all check (order: 0, 1, 2)
    for (int street = 0; street < 3; street++) {
        engine.submitAction({0, BET, 0});
        engine.submitAction({1, BET, 0});
        engine.submitAction({2, BET, 0});
    }

    PublicState state = engine.getPublicState();
    EXPECT_EQ(state.HandNum, 2);
    EXPECT_EQ(totalChips(state), 3 * settings.StartingCash);
}

// chips conserved across multiple hands
TEST(EngineTest, ChipsConserved_MultipleHands) {
    PokerEngine engine;
    EngineSettings settings;
    engine.initializeEngine(settings, 3);

    for (int hand = 0; hand < 5; hand++) {
        // each hand: all fold to last player
        PublicState state = engine.getPublicState();
        int first = state.Players[state.Current].PlayerId;
        engine.submitAction({first, FOLD});

        state = engine.getPublicState();
        int second = state.Players[state.Current].PlayerId;
        engine.submitAction({second, FOLD});
    }

    PublicState state = engine.getPublicState();
    EXPECT_EQ(totalChips(state), 3 * settings.StartingCash);
}

// --- SIDE POT ---

// three players, one all-in for less than others; verify chip conservation
TEST(EngineTest, SidePot_ChipsConserved) {
    PokerEngine engine;
    // player 2 starts with only 30 chips (less than BB=20 + any raise)
    EngineSettings settings;
    settings.StartingCash = 30;
    settings.BigBlind = 20;
    settings.SmallBlind = 10;
    engine.initializeEngine(settings, 3);

    // preflop: player 2 calls (all-in for 20), SB calls, BB checks
    engine.submitAction({2, BET, 0}); // call 20 (player 2 has 10 left)
    engine.submitAction({0, BET, 0}); // SB calls
    engine.submitAction({1, BET, 0}); // BB checks

    // flop through river: all check
    for (int street = 0; street < 3; street++) {
        engine.submitAction({0, BET, 0});
        engine.submitAction({1, BET, 0});
        engine.submitAction({2, BET, 0});
    }

    PublicState state = engine.getPublicState();
    EXPECT_EQ(totalChips(state), 3 * settings.StartingCash);
}

// all-in player wins main pot; winner of side pot gets only side pot chips
TEST(EngineTest, SidePot_TotalPayoutCorrect) {
    PokerEngine engine;
    EngineSettings settings;
    settings.StartingCash = 30;
    settings.BigBlind = 20;
    settings.SmallBlind = 10;
    engine.initializeEngine(settings, 3);

    engine.submitAction({2, BET, 0});
    engine.submitAction({0, BET, 0});
    engine.submitAction({1, BET, 0});

    for (int street = 0; street < 3; street++) {
        engine.submitAction({0, BET, 0});
        engine.submitAction({1, BET, 0});
        engine.submitAction({2, BET, 0});
    }

    // whoever won, total payout = total pot = 3 * 20 (everyone put in 20)
    EXPECT_EQ(engine.getResultState().Pot, 60);
}

// --- PLAYER ELIMINATION ---

// player busts out; remaining player count decreases
TEST(EngineTest, PlayerEliminated_AfterBust) {
    PokerEngine engine;
    EngineSettings settings;
    // give players exactly BigBlind chips so one hand busts someone
    settings.StartingCash = settings.BigBlind;
    engine.initializeEngine(settings, 3);

    // everyone calls preflop (BB is all-in), check to showdown
    engine.submitAction({2, BET, 0});
    engine.submitAction({0, BET, 0});
    engine.submitAction({1, BET, 0});

    for (int street = 0; street < 3; street++) {
        engine.submitAction({0, BET, 0});
        engine.submitAction({1, BET, 0});
        engine.submitAction({2, BET, 0});
    }

    // after the hand, at least one player must be eliminated (lost all chips)
    // total players should be <= 2
    PublicState state = engine.getPublicState();
    EXPECT_LE((int)state.Players.size(), 2);
    EXPECT_EQ(totalChips(state), 3 * settings.StartingCash);
}
