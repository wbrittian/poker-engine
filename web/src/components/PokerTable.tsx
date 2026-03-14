import { CardInfo, GameState, HandState, HUMAN_ID, STAGE_NAMES } from '../engine/types';
import { Card } from './Card';
import { PlayerSeat } from './PlayerSeat';

// Maps player ID to table seat position for up to 4 players.
// Player 0 (human) is always at the bottom.
const SEAT_POSITIONS: Record<number, 'bottom' | 'left' | 'top' | 'right'> = {
  0: 'bottom',
  1: 'left',
  2: 'top',
  3: 'right',
};

interface Props {
  gameState: GameState;
  handState: HandState;
  isHumanTurn: boolean;
}

export function PokerTable({ gameState, handState, isHumanTurn }: Props) {
  const { players, stage, current, smallBlind, pot, currentBet, community } = gameState;
  const bbIdx = (smallBlind + 1) % players.length;
  const stageName = STAGE_NAMES[stage] ?? '';

  const humanPlayer = players.find((p) => p.playerId === HUMAN_ID);

  return (
    <div className="table-container">
      {/* Player seats arranged around the table */}
      {players.map((player, idx) => {
        const position = SEAT_POSITIONS[player.playerId] ?? 'top';
        const isCurrentTurn = idx === current;
        const isHuman = player.playerId === HUMAN_ID;

        return (
          <PlayerSeat
            key={player.playerId}
            player={player}
            isCurrentTurn={isCurrentTurn}
            isSmallBlind={idx === smallBlind}
            isBigBlind={idx === bbIdx}
            holeCards={isHuman ? handState.hand : undefined}
            position={position}
          />
        );
      })}

      {/* Felt surface */}
      <div className="table-felt">
        {/* Stage + pot info */}
        <div className="table-info">
          <span className="table-stage">{stageName}</span>
          <span className="table-pot">Pot: ${pot}</span>
          {currentBet > 0 && (
            <span className="table-bet">Bet: ${currentBet}</span>
          )}
        </div>

        {/* Community cards */}
        <div className="community-cards">
          {community.length === 0 ? (
            <span className="community-empty">—</span>
          ) : (
            community.map((card: CardInfo, i: number) => (
              <Card key={i} card={card} />
            ))
          )}
        </div>

        {/* "Waiting for bots…" hint */}
        {!isHumanTurn && stage !== 0 && (
          <div className="table-waiting">thinking…</div>
        )}
      </div>

      {/* Hand number + human stack reminder */}
      <div className="table-footer">
        <span className="hand-num">Hand #{gameState.handNum}</span>
        {humanPlayer && (
          <span className="human-stack">Your stack: ${humanPlayer.cash}</span>
        )}
      </div>
    </div>
  );
}
