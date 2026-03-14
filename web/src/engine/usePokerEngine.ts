import { useCallback, useEffect, useRef, useState } from 'react';
import {
  ACTION_BET,
  ACTION_FOLD,
  BIG_BLIND,
  GameState,
  HandState,
  HUMAN_ID,
  NUM_PLAYERS,
  ResultState,
  SMALL_BLIND,
  STARTING_CASH,
} from './types';

// Delay (ms) before a bot submits its action — gives the user time to see
// what's happening before the table state changes.
const BOT_DELAY_MS = 700;

declare global {
  interface Window {
    // Emscripten factory function injected by poker_engine.js
    PokerEngineModule: (opts?: object) => Promise<GameManagerModule>;
  }
}

interface GameManagerModule {
  GameManager: new () => GameManagerInstance;
}

interface GameManagerInstance {
  init(bigBlind: number, smallBlind: number, startingCash: number, numPlayers: number): void;
  getPublicState(): string;
  getPlayerState(): string;
  getResultState(): string;
  humanAction(type: number, amount: number): boolean;
  botAction(): boolean;
  isGameOver(): boolean;
  isHumanTurn(): boolean;
}

export interface PokerEngineState {
  loaded: boolean;
  gameState: GameState | null;
  handState: HandState | null;
  resultState: ResultState | null;
  showResult: boolean;
  isGameOver: boolean;
  submitCall: () => void;
  submitFold: () => void;
  submitBet: (amount: number) => void;
  dismissResult: () => void;
}

export function usePokerEngine(): PokerEngineState {
  const managerRef = useRef<GameManagerInstance | null>(null);
  const [loaded, setLoaded] = useState(false);
  const [gameState, setGameState] = useState<GameState | null>(null);
  const [handState, setHandState] = useState<HandState | null>(null);
  const [resultState, setResultState] = useState<ResultState | null>(null);
  const [showResult, setShowResult] = useState(false);
  const [isOver, setIsOver] = useState(false);

  // Track hand number to detect transitions between hands.
  const prevHandNumRef = useRef<number>(-1);
  // Prevent concurrent bot-action timers.
  const botTimerRef = useRef<ReturnType<typeof setTimeout> | null>(null);

  const readState = useCallback((): GameState | null => {
    const m = managerRef.current;
    if (!m) return null;
    return JSON.parse(m.getPublicState()) as GameState;
  }, []);

  // Refresh React state from the engine after any action.
  const refresh = useCallback(() => {
    const m = managerRef.current;
    if (!m) return;

    const gs = JSON.parse(m.getPublicState()) as GameState;
    const hs = JSON.parse(m.getPlayerState()) as HandState;

    // Detect hand transition — the engine auto-advances so handNum increments.
    if (prevHandNumRef.current !== -1 && gs.handNum !== prevHandNumRef.current) {
      const rs = JSON.parse(m.getResultState()) as ResultState;
      setResultState(rs);
      setShowResult(true);
    }
    prevHandNumRef.current = gs.handNum;

    setGameState(gs);
    setHandState(hs);

    if (m.isGameOver()) {
      setIsOver(true);
    }
  }, []);

  // Trigger bot actions automatically with a small delay.
  useEffect(() => {
    if (!loaded || !gameState) return;
    if (showResult) return; // pause bot while result overlay is visible
    // stage 0 = INACTIVE (game over)
    if (gameState.stage === 0) return;

    const currentPid = gameState.players[gameState.current]?.playerId;
    if (currentPid === HUMAN_ID) return; // human's turn

    // Schedule bot action.
    if (botTimerRef.current) clearTimeout(botTimerRef.current);
    botTimerRef.current = setTimeout(() => {
      managerRef.current?.botAction();
      refresh();
    }, BOT_DELAY_MS);

    return () => {
      if (botTimerRef.current) clearTimeout(botTimerRef.current);
    };
  }, [gameState, loaded, showResult, refresh]);

  // Load the Wasm module once on mount.
  useEffect(() => {
    if (typeof window === 'undefined') return;

    const script = document.createElement('script');
    script.src = '/poker_engine.js';
    script.onload = async () => {
      const mod = await window.PokerEngineModule();
      const manager = new mod.GameManager();
      manager.init(BIG_BLIND, SMALL_BLIND, STARTING_CASH, NUM_PLAYERS);
      managerRef.current = manager;

      const gs = JSON.parse(manager.getPublicState()) as GameState;
      const hs = JSON.parse(manager.getPlayerState()) as HandState;
      prevHandNumRef.current = gs.handNum;
      setGameState(gs);
      setHandState(hs);
      setLoaded(true);
    };
    script.onerror = () => {
      console.error(
        'Failed to load poker_engine.js. Run `make wasm` first to generate the Wasm build.',
      );
    };
    document.head.appendChild(script);
    return () => {
      document.head.removeChild(script);
    };
  }, []);

  const submitCall = useCallback(() => {
    managerRef.current?.humanAction(ACTION_BET, 0);
    refresh();
  }, [refresh]);

  const submitFold = useCallback(() => {
    managerRef.current?.humanAction(ACTION_FOLD, 0);
    refresh();
  }, [refresh]);

  const submitBet = useCallback(
    (amount: number) => {
      managerRef.current?.humanAction(ACTION_BET, amount);
      refresh();
    },
    [refresh],
  );

  const dismissResult = useCallback(() => {
    setShowResult(false);
    // Re-read state in case the game is over after dismissal.
    const gs = readState();
    if (gs) setGameState(gs);
  }, [readState]);

  return {
    loaded,
    gameState,
    handState,
    resultState,
    showResult,
    isGameOver: isOver,
    submitCall,
    submitFold,
    submitBet,
    dismissResult,
  };
}
