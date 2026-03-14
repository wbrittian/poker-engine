import { CardInfo, RANK_LABELS, SUIT_IS_RED, SUIT_SYMBOLS } from '../engine/types';

interface Props {
  card: CardInfo;
  faceDown?: boolean;
  small?: boolean;
}

export function Card({ card, faceDown = false, small = false }: Props) {
  const size = small ? 'card-small' : 'card';

  if (faceDown) {
    return <div className={`${size} card-back`}>🂠</div>;
  }

  const rank = RANK_LABELS[card.rank];
  const suit = SUIT_SYMBOLS[card.suit];
  const red = SUIT_IS_RED[card.suit];

  return (
    <div className={`${size} ${red ? 'card-red' : 'card-black'}`}>
      <span className="card-rank">{rank}</span>
      <span className="card-suit">{suit}</span>
    </div>
  );
}
