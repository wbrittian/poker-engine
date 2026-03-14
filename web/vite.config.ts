import { defineConfig } from 'vite';
import react from '@vitejs/plugin-react';

export default defineConfig({
  plugins: [react()],
  // Exclude the Wasm glue script from Vite's module graph — it's loaded via a
  // <script> tag in the hook so Emscripten's own module format is preserved.
  optimizeDeps: {
    exclude: ['poker_engine'],
  },
});
