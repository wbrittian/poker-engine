import { defineConfig } from 'vite';
import react from '@vitejs/plugin-react';

export default defineConfig({
  plugins: [react()],
  // Use /poker-engine/ as the base when deploying to GitHub Pages
  // (https://williambrittian.github.io/poker-engine/).
  // Locally (make web / npm run dev) the base stays at /.
  base: '/',
  optimizeDeps: {
    exclude: ['poker_engine'],
  },
});
