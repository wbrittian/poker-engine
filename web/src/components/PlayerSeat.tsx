import { CardInfo, PlayerInfo, PLAYER_NAMES } from '../engine/types';
import { Card } from './Card';

interface Props {
  player: PlayerInfo;
  isCurrentTurn: boolean;
  isSmallBlind: boolean;
  isBigBlind: boolean;
  holeCards?: CardInfo[]; // only provided for human player
  position: 'bottom' | 'left' | 'top' | 'right' | 'top-left' | 'top-right';
}

export function PlayerSeat({
  player,
  isCurrentTurn,
  isSmallBlind,
  isBigBlind,
  holeCards,
  position,
}: Props) {
  const name = PLAYER_NAMES[player.playerId] ?? `Player ${player.playerId}`;
  const folded = !player.active;
  const allIn = player.active && player.cash === 0;

  return (
    <div className={`seat seat-${position} ${isCurrentTurn ? 'seat-active' : ''} ${folded ? 'seat-folded' : ''}`}>
      {/* Cards — shown only for human (hole cards) or as face-down for bots */}
      {holeCards ? (
        <div className="seat-cards">
          {holeCards.map((c, i) => (
            <Card key={i} card={c} small />
          ))}
        </div>
      ) : (
        <div className="seat-cards seat-cards-bot">
          <Card card={{ rank: 0, suit: 0 }} faceDown small />
          <Card card={{ rank: 0, suit: 0 }} faceDown small />
        </div>
      )}

      {/* Name + status badges */}
      <div className="seat-info">
        <div className="seat-name">
          {isCurrentTurn && <span className="turn-dot" />}
          {name}
        </div>
        <div className="seat-badges">
          {isSmallBlind && <span className="badge badge-sb">SB</span>}
          {isBigBlind && <span className="badge badge-bb">BB</span>}
          {allIn && <span className="badge badge-allin">ALL IN</span>}
          {folded && <span className="badge badge-folded">FOLDED</span>}
        </div>
      </div>

      {/* Stack + current bet */}
      <div className="seat-chips">
        <span className="chip-stack">
          {folded ? '—' : `$${player.cash}`}
        </span>
        {player.bet > 0 && (
          <span className="chip-bet">bet ${player.bet}</span>
        )}
      </div>
    </div>
  );
}
