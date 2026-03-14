import { PLAYER_NAMES, ResultState } from '../engine/types';
import { Card } from './Card';

interface Props {
  result: ResultState;
  onDismiss: () => void;
}

export function ResultOverlay({ result, onDismiss }: Props) {
  const winnerName = PLAYER_NAMES[result.winner] ?? `Player ${result.winner}`;

  return (
    <div className="overlay-backdrop" onClick={onDismiss}>
      <div className="overlay-card" onClick={(e) => e.stopPropagation()}>
        <div className="overlay-winner">
          🏆 {winnerName} wins ${result.pot}!
        </div>

        {result.players.length > 0 && (
          <div className="overlay-hands">
            {result.players.map((pid, i) => (
              <div key={pid} className="overlay-hand-row">
                <span className="overlay-hand-name">
                  {PLAYER_NAMES[pid] ?? `Player ${pid}`}
                </span>
                <div className="overlay-hand-cards">
                  {result.hands[i]?.map((card, j) => (
                    <Card key={j} card={card} small />
                  ))}
                </div>
              </div>
            ))}
          </div>
        )}

        <button className="btn btn-continue" onClick={onDismiss}>
          Continue →
        </button>
      </div>
    </div>
  );
}
