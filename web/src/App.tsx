import { ActionPanel } from './components/ActionPanel';
import { PokerTable } from './components/PokerTable';
import { ResultOverlay } from './components/ResultOverlay';
import { HUMAN_ID } from './engine/types';
import { usePokerEngine } from './engine/usePokerEngine';

export default function App() {
  const {
    loaded,
    gameState,
    handState,
    resultState,
    showResult,
    isGameOver,
    actionLog,
    submitCall,
    submitFold,
    submitBet,
    dismissResult,
  } = usePokerEngine();

  if (!loaded || !gameState || !handState) {
    return (
      <div className="loading-screen">
        <div className="loading-spinner" />
        <p>Loading engine…</p>
        <p className="loading-hint">
          Make sure <code>make wasm</code> has been run and{' '}
          <code>web/public/poker_engine.js</code> exists.
        </p>
      </div>
    );
  }

  if (isGameOver) {
    const winner = gameState.players[0];
    return (
      <div className="gameover-screen">
        <div className="gameover-card">
          <h1>Game Over</h1>
          <p>
            {winner?.playerId === HUMAN_ID
              ? '🏆 You win the whole table!'
              : `${winner ? `Player ${winner.playerId}` : 'Someone'} takes it all.`}
          </p>
          <button className="btn btn-continue" onClick={() => window.location.reload()}>
            Play again
          </button>
        </div>
      </div>
    );
  }

  const humanPlayer = gameState.players.find((p) => p.playerId === HUMAN_ID);
  const isHumanTurn = gameState.players[gameState.current]?.playerId === HUMAN_ID;

  return (
    <div className="app">
      <PokerTable
        gameState={gameState}
        handState={handState}
        isHumanTurn={isHumanTurn}
        actionLog={actionLog}
      />

      {isHumanTurn && humanPlayer && (
        <ActionPanel
          currentBet={gameState.currentBet}
          playerBet={humanPlayer.bet}
          playerCash={humanPlayer.cash}
          pot={gameState.pot}
          onCall={submitCall}
          onFold={submitFold}
          onBet={submitBet}
        />
      )}

      {showResult && resultState && (
        <ResultOverlay result={resultState} onDismiss={dismissResult} />
      )}
    </div>
  );
}
