// Mirrors the C++ enums / structs from structs.hpp and deck.hpp.

export interface CardInfo {
  rank: number; // 0=2 … 12=A
  suit: number; // 0=Spades, 1=Hearts, 2=Clubs, 3=Diamonds
}

export interface PlayerInfo {
  playerId: number;
  active: boolean;
  cash: number;
  bet: number;
  potSplit: number;
}

// stage values: 0=INACTIVE, 1=PREFLOP, 2=FLOP, 3=TURN, 4=RIVER, 5=SHOWDOWN
export interface GameState {
  handNum: number;
  stage: number;
  current: number; // index into players array
  smallBlind: number; // index of SB seat
  pot: number;
  currentBet: number;
  players: PlayerInfo[];
  community: CardInfo[];
}

export interface HandState {
  hand: CardInfo[];
}

export interface ResultState {
  winner: number; // player ID
  pot: number;
  players: number[]; // player IDs that went to showdown
  hands: CardInfo[][]; // hole cards for each player in `players`
}

export const STAGE_NAMES: Record<number, string> = {
  0: 'Inactive',
  1: 'Pre-Flop',
  2: 'Flop',
  3: 'Turn',
  4: 'River',
  5: 'Showdown',
};

export const RANK_LABELS = ['2', '3', '4', '5', '6', '7', '8', '9', '10', 'J', 'Q', 'K', 'A'];
export const SUIT_SYMBOLS = ['♠', '♥', '♣', '♦'];
export const SUIT_IS_RED = [false, true, false, true];

// ActionTypes: 1 = BET/CALL/CHECK, 2 = FOLD
export const ACTION_BET = 1;
export const ACTION_FOLD = 2;

export const HUMAN_ID = 0;
export const NUM_PLAYERS = 4;
export const BIG_BLIND = 20;
export const SMALL_BLIND = 10;
export const STARTING_CASH = 1000;

export const PLAYER_NAMES: Record<number, string> = {
  0: 'You',
  1: 'Bot 1',
  2: 'Bot 2',
  3: 'Bot 3',
};
