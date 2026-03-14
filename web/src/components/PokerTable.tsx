import { CardInfo, GameState, HandState, HUMAN_ID, PLAYER_NAMES, STAGE_NAMES } from '../engine/types';
import { Card } from './Card';
import { PlayerSeat } from './PlayerSeat';

// Fixed seat positions by player ID.
const SEAT_POSITIONS: Record<number, 'top' | 'left' | 'right' | 'bottom'> = {
  0: 'bottom',
  1: 'left',
  2: 'top',
  3: 'right',
};

interface Props {
  gameState: GameState;
  handState: HandState;
  isHumanTurn: boolean;
  actionLog: string[];
}

function StatusBar({ gameState, isHumanTurn }: { gameState: GameState; isHumanTurn: boolean }) {
  const { players, current, currentBet, stage } = gameState;
  if (stage === 0) return null;

  const currentPlayer = players[current];
  if (!currentPlayer) return null;

  if (isHumanTurn) {
    const me = players.find((p) => p.playerId === HUMAN_ID);
    const toCall = currentBet - (me?.bet ?? 0);
    const msg = toCall === 0 ? 'Your turn — check or bet' : `Your turn — call $${toCall} or fold`;
    return <div className="status-bar status-bar--you">🎯 {msg}</div>;
  }

  const name = PLAYER_NAMES[currentPlayer.playerId] ?? `Player ${currentPlayer.playerId}`;
  return <div className="status-bar status-bar--bot">⏳ {name} is thinking…</div>;
}

export function PokerTable({ gameState, handState, isHumanTurn, actionLog }: Props) {
  const { players, stage, current, smallBlind, pot, currentBet, community } = gameState;
  const bbIdx = (smallBlind + 1) % players.length;
  const stageName = STAGE_NAMES[stage] ?? '';

  // Map each grid position to its player (if still in the game).
  const byPos = {
    top:    players.find((p) => SEAT_POSITIONS[p.playerId] === 'top'),
    left:   players.find((p) => SEAT_POSITIONS[p.playerId] === 'left'),
    right:  players.find((p) => SEAT_POSITIONS[p.playerId] === 'right'),
    bottom: players.find((p) => SEAT_POSITIONS[p.playerId] === 'bottom'),
  };

  function renderSeat(pos: 'top' | 'left' | 'right' | 'bottom') {
    const player = byPos[pos];
    if (!player) return <div />;
    const idx = players.indexOf(player);
    const isHuman = player.playerId === HUMAN_ID;
    return (
      <PlayerSeat
        player={player}
        isCurrentTurn={idx === current}
        isSmallBlind={idx === smallBlind}
        isBigBlind={idx === bbIdx}
        holeCards={isHuman ? handState.hand : undefined}
        position={pos}
      />
    );
  }

  return (
    <div className="table-wrapper">
      <StatusBar gameState={gameState} isHumanTurn={isHumanTurn} />

      <div className="table-grid">
        {/* Top seat */}
        <div className="grid-corner" />
        <div className="grid-top">{renderSeat('top')}</div>
        <div className="grid-corner" />

        {/* Middle row: left seat | felt | right seat */}
        <div className="grid-left">{renderSeat('left')}</div>

        <div className="table-felt">
          <div className="felt-stage">{stageName}</div>

          <div className="community-cards">
            {community.length === 0 ? (
              <span className="community-empty">— waiting for deal —</span>
            ) : (
              community.map((card: CardInfo, i: number) => <Card key={i} card={card} />)
            )}
          </div>

          <div className="felt-pot-row">
            <span className="felt-pot">Pot: ${pot}</span>
            {currentBet > 0 && <span className="felt-bet">To call: ${currentBet}</span>}
          </div>

          {!isHumanTurn && stage !== 0 && (
            <div className="felt-thinking">thinking…</div>
          )}
        </div>

        <div className="grid-right">{renderSeat('right')}</div>

        {/* Bottom seat */}
        <div className="grid-corner" />
        <div className="grid-bottom">{renderSeat('bottom')}</div>
        <div className="grid-corner" />
      </div>

      {/* Action log + hand counter */}
      <div className="table-footer">
        <span className="hand-num">Hand #{gameState.handNum}</span>
        <div className="action-log">
          {actionLog.map((entry, i) => (
            <span key={i} className="log-entry" style={{ opacity: 1 - i * 0.18 }}>
              {entry}
            </span>
          ))}
        </div>
      </div>
    </div>
  );
}
