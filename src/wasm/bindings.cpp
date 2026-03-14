/*bindings.cpp*/

//
// Emscripten bindings — exposes a GameManager wrapper to JavaScript via WebAssembly.
// The GameManager owns the PokerEngine and all Bot instances, and serializes state
// to JSON strings so the JS side never touches raw C++ objects.
//
// William Brittian
// 2025
//

#include <emscripten/bind.h>

#include <sstream>
#include <string>
#include <vector>

#include "../bots/bot.hpp"
#include "../core/engine.hpp"

using namespace emscripten;

// ---------------------------------------------------------------------------
// JSON helpers
// ---------------------------------------------------------------------------

static std::string cardJson(const Card& c) {
    std::ostringstream o;
    o << "{\"rank\":" << static_cast<int>(c.Rank) << ",\"suit\":" << static_cast<int>(c.Suit) << "}";
    return o.str();
}

static std::string cardsJson(const std::vector<Card>& cards) {
    std::ostringstream o;
    o << "[";
    for (size_t i = 0; i < cards.size(); i++) {
        if (i) o << ",";
        o << cardJson(cards[i]);
    }
    o << "]";
    return o.str();
}

static std::string publicStateJson(const PublicState& s) {
    std::ostringstream o;
    o << "{";
    o << "\"handNum\":" << s.HandNum << ",";
    o << "\"stage\":" << static_cast<int>(s.EngineStage) << ",";
    o << "\"current\":" << s.Current << ",";
    o << "\"smallBlind\":" << s.SmallBlind << ",";
    o << "\"pot\":" << s.Pot << ",";
    o << "\"currentBet\":" << s.CurrentBet << ",";
    o << "\"community\":" << cardsJson(s.Community) << ",";
    o << "\"players\":[";
    for (size_t i = 0; i < s.Players.size(); i++) {
        if (i) o << ",";
        const auto& p = s.Players[i];
        o << "{\"playerId\":" << p.PlayerId
          << ",\"active\":" << (p.Active ? "true" : "false")
          << ",\"cash\":" << p.Cash
          << ",\"bet\":" << p.Bet
          << ",\"potSplit\":" << p.PotSplit
          << "}";
    }
    o << "]}";
    return o.str();
}

static std::string playerStateJson(const PlayerState& s) {
    return "{\"hand\":" + cardsJson(s.Hand) + "}";
}

static std::string resultStateJson(const ResultState& s) {
    std::ostringstream o;
    o << "{";
    o << "\"winner\":" << s.Winner << ",";
    o << "\"pot\":" << s.Pot << ",";
    o << "\"players\":[";
    for (size_t i = 0; i < s.Players.size(); i++) {
        if (i) o << ",";
        o << s.Players[i];
    }
    o << "],";
    o << "\"hands\":[";
    for (size_t i = 0; i < s.Hands.size(); i++) {
        if (i) o << ",";
        o << cardsJson(s.Hands[i]);
    }
    o << "]}";
    return o.str();
}

// ---------------------------------------------------------------------------
// GameManager — the only class exposed to JavaScript
// ---------------------------------------------------------------------------

class GameManager {
    PokerEngine engine;
    std::vector<Bot> bots;
    int humanId = 0;

  public:
    // Initialise (or re-initialise) the engine. numPlayers includes the human.
    void init(int bigBlind, int smallBlind, int startingCash, int numPlayers) {
        bots.clear();
        for (int id = 1; id < numPlayers; id++) {
            bots.emplace_back(id);
        }
        EngineSettings settings;
        settings.BigBlind = bigBlind;
        settings.SmallBlind = smallBlind;
        settings.StartingCash = startingCash;
        engine = PokerEngine();
        engine.initializeEngine(settings, numPlayers);
    }

    // JSON-serialised public game state (board, players, stage).
    std::string getPublicState() {
        return publicStateJson(engine.getPublicState());
    }

    // JSON-serialised private hand for the human player.
    std::string getPlayerState() {
        return playerStateJson(engine.getPlayerState(humanId));
    }

    // JSON-serialised result of the most recently completed hand.
    std::string getResultState() {
        return resultStateJson(engine.getResultState());
    }

    // Submit the human player's action.
    // type: 1 = BET/CALL/CHECK (amount=0 means call/check), 2 = FOLD.
    // Returns true if the engine accepted the action.
    bool humanAction(int type, int amount) {
        auto state = engine.getPublicState();
        int currentIdx = state.Current;
        int currentPid = state.Players[currentIdx].PlayerId;
        if (currentPid != humanId) return false;

        Action a;
        a.PlayerId = currentPid;
        a.Type = static_cast<ActionTypes>(type);
        a.Amount = amount;
        return engine.submitAction(a);
    }

    // Submit the current bot player's action automatically.
    // Returns true if the engine accepted the action.
    bool botAction() {
        auto state = engine.getPublicState();
        int currentIdx = state.Current;
        int currentPid = state.Players[currentIdx].PlayerId;

        for (auto& bot : bots) {
            if (bot.getId() == currentPid) {
                Action action = bot.getAction(state);
                action.PlayerId = currentPid;
                return engine.submitAction(action);
            }
        }
        return false;
    }

    // True when only one player remains and the game is definitively over.
    bool isGameOver() {
        auto state = engine.getPublicState();
        return state.EngineStage == INACTIVE && state.Players.size() <= 1;
    }

    // True when the current seat belongs to the human player.
    bool isHumanTurn() {
        auto state = engine.getPublicState();
        if (state.EngineStage == INACTIVE) return false;
        return state.Players[state.Current].PlayerId == humanId;
    }
};

// ---------------------------------------------------------------------------
// Emscripten bindings
// ---------------------------------------------------------------------------

EMSCRIPTEN_BINDINGS(poker_engine) {
    class_<GameManager>("GameManager")
        .constructor<>()
        .function("init", &GameManager::init)
        .function("getPublicState", &GameManager::getPublicState)
        .function("getPlayerState", &GameManager::getPlayerState)
        .function("getResultState", &GameManager::getResultState)
        .function("humanAction", &GameManager::humanAction)
        .function("botAction", &GameManager::botAction)
        .function("isGameOver", &GameManager::isGameOver)
        .function("isHumanTurn", &GameManager::isHumanTurn);
}
