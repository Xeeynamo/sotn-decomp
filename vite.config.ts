import { defineConfig } from "vite";
import react from "@vitejs/plugin-react";

// The site is deployed to the root of a GitHub Pages domain, so base is "/".
export default defineConfig({
  plugins: [react()],
  build: {
    outDir: "dist",
  },
});
