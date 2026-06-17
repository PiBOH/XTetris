# XTetris — Sito GitHub Pages

Questa è la **GitHub Pages** del progetto
[PiBOH/XTetris](https://github.com/PiBOH/XTetris): una pagina
statica che mostra il nome del progetto, il contenuto del README
e i link per scaricare il repository.

## File

| File        | Descrizione                                              |
|-------------|----------------------------------------------------------|
| `index.html`| Pagina principale (hero, README, download, build, …).    |
| `style.css` | Tema ispirato ai colori dei tetramini del Tetris.        |
| `script.js` | Carica il README e il CHANGELOG via fetch e li renderizza. |
| `404.html`  | Pagina di fallback per GitHub Pages.                     |

## Pubblicazione

GitHub Pages può servire questa cartella direttamente dal branch
`main` (root) — basta fare push dei file e abilitare Pages dalle
impostazioni del repository. Il sito sarà visibile all'indirizzo:

```
https://piboh.github.io/XTetris/
```

## Note

* Lo script `script.js` recupera i file `README.md` e `CHANGELOG.md`
  direttamente da `raw.githubusercontent.com`, quindi non c'è
  bisogno di duplicare i contenuti: la pagina si aggiorna
  automaticamente ad ogni modifica al repository.
* La sezione download offre sia il link diretto all'archivio
  precompilato in `.releases/`, sia il classico comando
  `git clone`, sia il download dell'intero sorgente come `.zip`.
