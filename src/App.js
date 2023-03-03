import './App.css';
import './Chart'
import React from 'react';
import { ChartsVersion } from './ChartsVersion';

function App() {
  return (
    <div className="App">
      <h2>Castlevania: Symphony of the Night decompilation</h2>
      <div >
        <p>GitHub repo: <a href="https://github.com/xeeynamo/sotn-decomp" target="_blank" rel="noopener noreferrer">github.com/xeeynamo/sotn-decomp</a></p>
        <p>Discord server: <a href="https://sotn-discord.xee.dev/" target="_blank" rel="noopener noreferrer">sotn-discord.xee.dev</a></p>
      </div>
      <ChartsVersion name="PS1 US" gameVersion="us"/>
    </div>
  );
}

export default App;
