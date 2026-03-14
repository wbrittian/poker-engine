import { useState } from 'react';
import { BIG_BLIND } from '../engine/types';

interface Props {
  currentBet: number;
  playerBet: number;
  playerCash: number;
  pot: number;
  onCall: () => void;
  onFold: () => void;
  onBet: (amount: number) => void;
}

export function ActionPanel({
  currentBet,
  playerBet,
  playerCash,
  pot,
  onCall,
  onFold,
  onBet,
}: Props) {
  const toCall = Math.max(0, currentBet - playerBet);
  const canCheck = toCall === 0;
  const minRaise = Math.max(2 * currentBet, BIG_BLIND * 2);
  const canRaise = playerCash > toCall;

  const [raiseAmount, setRaiseAmount] = useState(minRaise);
  const [showRaise, setShowRaise] = useState(false);

  const clampedRaise = Math.min(Math.max(raiseAmount, minRaise), playerCash);

  function handleRaiseSubmit() {
    onBet(clampedRaise);
    setShowRaise(false);
  }

  // Quick-bet presets
  const halfPot = Math.max(minRaise, Math.floor(pot / 2));
  const fullPot = Math.max(minRaise, pot);

  return (
    <div className="action-panel">
      {showRaise ? (
        <div className="raise-controls">
          <div className="raise-presets">
            <button className="btn btn-preset" onClick={() => setRaiseAmount(halfPot)}>½ pot</button>
            <button className="btn btn-preset" onClick={() => setRaiseAmount(fullPot)}>pot</button>
            <button className="btn btn-preset" onClick={() => setRaiseAmount(playerCash)}>all in</button>
          </div>
          <div className="raise-slider-row">
            <input
              type="range"
              min={minRaise}
              max={playerCash}
              step={BIG_BLIND}
              value={clampedRaise}
              onChange={(e) => setRaiseAmount(Number(e.target.value))}
              className="raise-slider"
            />
            <span className="raise-amount">${clampedRaise}</span>
          </div>
          <div className="raise-actions">
            <button className="btn btn-cancel" onClick={() => setShowRaise(false)}>Cancel</button>
            <button className="btn btn-confirm" onClick={handleRaiseSubmit}>
              {currentBet === 0 ? 'Bet' : 'Raise'} ${clampedRaise}
            </button>
          </div>
        </div>
      ) : (
        <div className="action-buttons">
          <button className="btn btn-fold" onClick={onFold}>Fold</button>
          <button className="btn btn-call" onClick={onCall}>
            {canCheck ? 'Check' : `Call $${toCall}`}
          </button>
          {canRaise && (
            <button className="btn btn-raise" onClick={() => { setRaiseAmount(minRaise); setShowRaise(true); }}>
              {currentBet === 0 ? 'Bet' : 'Raise'}
            </button>
          )}
        </div>
      )}
    </div>
  );
}
