import { CardInfo, PlayerInfo, PLAYER_NAMES } from '../engine/types';
import { Card } from './Card';

interface Props {
  player: PlayerInfo;
  isCurrentTurn: boolean;
  isSmallBlind: boolean;
  isBigBlind: boolean;
  holeCards?: CardInfo[];
  position: 'top' | 'left' | 'right' | 'bottom';
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
  const isHuman = !!holeCards;

  return (
    <div className={[
      'seat',
      `seat-${position}`,
      isCurrentTurn ? 'seat-active' : '',
      folded ? 'seat-folded' : '',
      isHuman ? 'seat-human' : '',
    ].join(' ')}>

      {/* Cards */}
      <div className="seat-cards">
        {holeCards ? (
          holeCards.map((c, i) => <Card key={i} card={c} small />)
        ) : (
          <>
            <Card card={{ rank: 0, suit: 0 }} faceDown small />
            <Card card={{ rank: 0, suit: 0 }} faceDown small />
          </>
        )}
      </div>

      {/* Info chip */}
      <div className="seat-chip">
        {isCurrentTurn && <span className="turn-dot" />}
        <div className="seat-name">{name}</div>
        <div className="seat-meta">
          {folded ? (
            <span className="badge badge-folded">FOLDED</span>
          ) : allIn ? (
            <span className="badge badge-allin">ALL IN</span>
          ) : (
            <span className="seat-cash">${player.cash}</span>
          )}
          {isSmallBlind && <span className="badge badge-sb">SB</span>}
          {isBigBlind  && <span className="badge badge-bb">BB</span>}
        </div>
        {player.bet > 0 && !folded && (
          <div className="seat-bet">bet ${player.bet}</div>
        )}
      </div>
    </div>
  );
}
