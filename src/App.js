import './App.css';
import './Chart'
import React from 'react';
import { ChartsVersion } from './ChartsVersion';
import gameMetadata from './gamemeta'

function App() {
  return (
    <div className="App">
      <h1>{gameMetadata.name} decompilation</h1>
      <div>
        {gameMetadata.links.map(l =>
          <a className="header-link" target="_blank" rel="noopener noreferrer"
            href={l.url}>{l.name}</a>
        )}
      </div>
      <div>
        {gameMetadata.versions.map(v =>
          <ChartsVersion
            gameId={gameMetadata.id}
            version={v}
            labels={gameMetadata.labels}
            overlays={gameMetadata.overlays}
          />
        )}
      </div>
    </div>
  );
}

export default App;
