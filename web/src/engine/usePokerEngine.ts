import { useCallback, useEffect, useRef, useState } from 'react';
import {
  ACTION_BET,
  ACTION_FOLD,
  BIG_BLIND,
  GameState,
  HandState,
  HUMAN_ID,
  NUM_PLAYERS,
  PLAYER_NAMES,
  ResultState,
  SMALL_BLIND,
  STARTING_CASH,
} from './types';

const BOT_DELAY_MS = 700;
const MAX_LOG = 5;

declare global {
  interface Window {
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
  actionLog: string[];
  submitCall: () => void;
  submitFold: () => void;
  submitBet: (amount: number) => void;
  dismissResult: () => void;
}

function describeAction(
  pid: number,
  prevBet: number,
  prevCurrentBet: number,
  newActive: boolean,
  newBet: number,
): string {
  const name = PLAYER_NAMES[pid] ?? `Player ${pid}`;
  if (!newActive) return `${name} folded`;
  if (newBet > prevBet) {
    if (newBet > prevCurrentBet) return `${name} raised to $${newBet}`;
    if (prevCurrentBet === 0) return `${name} checked`;
    return `${name} called $${newBet - prevBet}`;
  }
  return `${name} checked`;
}

export function usePokerEngine(): PokerEngineState {
  const managerRef = useRef<GameManagerInstance | null>(null);
  const [loaded, setLoaded] = useState(false);
  const [gameState, setGameState] = useState<GameState | null>(null);
  const [handState, setHandState] = useState<HandState | null>(null);
  const [resultState, setResultState] = useState<ResultState | null>(null);
  const [showResult, setShowResult] = useState(false);
  const [isOver, setIsOver] = useState(false);
  const [actionLog, setActionLog] = useState<string[]>([]);

  const prevHandNumRef = useRef<number>(-1);
  const botTimerRef = useRef<ReturnType<typeof setTimeout> | null>(null);

  const pushLog = useCallback((entry: string) => {
    setActionLog((prev) => [entry, ...prev].slice(0, MAX_LOG));
  }, []);

  const refreshState = useCallback(() => {
    const m = managerRef.current;
    if (!m) return;

    const gs = JSON.parse(m.getPublicState()) as GameState;
    const hs = JSON.parse(m.getPlayerState()) as HandState;

    if (prevHandNumRef.current !== -1 && gs.handNum !== prevHandNumRef.current) {
      const rs = JSON.parse(m.getResultState()) as ResultState;
      setResultState(rs);
      setShowResult(true);
    }
    prevHandNumRef.current = gs.handNum;

    setGameState(gs);
    setHandState(hs);
    if (m.isGameOver()) setIsOver(true);
  }, []);

  // Auto-fire bot actions.
  useEffect(() => {
    if (!loaded || !gameState) return;
    if (showResult) return;
    if (gameState.stage === 0) return;

    const currentPid = gameState.players[gameState.current]?.playerId;
    if (currentPid === HUMAN_ID) return;

    if (botTimerRef.current) clearTimeout(botTimerRef.current);
    botTimerRef.current = setTimeout(() => {
      const m = managerRef.current;
      if (!m) return;

      // Snapshot state before the action so we can describe it.
      const before = JSON.parse(m.getPublicState()) as GameState;
      const actor = before.players[before.current];
      const prevBet = actor?.bet ?? 0;
      const prevCurrentBet = before.currentBet;

      m.botAction();

      const after = JSON.parse(m.getPublicState()) as GameState;
      const actorAfter = after.players.find((p) => p.playerId === actor?.playerId);
      if (actor) {
        pushLog(
          describeAction(
            actor.playerId,
            prevBet,
            prevCurrentBet,
            actorAfter?.active ?? false,
            actorAfter?.bet ?? prevBet,
          ),
        );
      }

      refreshState();
    }, BOT_DELAY_MS);

    return () => { if (botTimerRef.current) clearTimeout(botTimerRef.current); };
  }, [gameState, loaded, showResult, refreshState, pushLog]);

  // Load the Wasm module once on mount.
  useEffect(() => {
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
    script.onerror = () => console.error('Failed to load poker_engine.js — run `make wasm` first.');
    document.head.appendChild(script);
    return () => { document.head.removeChild(script); };
  }, []);

  const submitCall = useCallback(() => {
    const m = managerRef.current;
    if (!m) return;
    const gs = JSON.parse(m.getPublicState()) as GameState;
    const me = gs.players.find((p) => p.playerId === HUMAN_ID);
    const toCall = gs.currentBet - (me?.bet ?? 0);
    m.humanAction(ACTION_BET, 0);
    pushLog(toCall === 0 ? 'You checked' : `You called $${toCall}`);
    refreshState();
  }, [refreshState, pushLog]);

  const submitFold = useCallback(() => {
    managerRef.current?.humanAction(ACTION_FOLD, 0);
    pushLog('You folded');
    refreshState();
  }, [refreshState, pushLog]);

  const submitBet = useCallback(
    (amount: number) => {
      const m = managerRef.current;
      if (!m) return;
      const gs = JSON.parse(m.getPublicState()) as GameState;
      m.humanAction(ACTION_BET, amount);
      pushLog(gs.currentBet === 0 ? `You bet $${amount}` : `You raised to $${amount}`);
      refreshState();
    },
    [refreshState, pushLog],
  );

  const dismissResult = useCallback(() => {
    setShowResult(false);
    refreshState();
  }, [refreshState]);

  return {
    loaded,
    gameState,
    handState,
    resultState,
    showResult,
    isGameOver: isOver,
    actionLog,
    submitCall,
    submitFold,
    submitBet,
    dismissResult,
  };
}
