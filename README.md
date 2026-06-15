# XTetris

XTetris è un progetto in **C** che implementa una variante testuale di **Tetris** eseguita da terminale, con una successiva adattazione per il web tramite **WebAssembly** e deploy automatico su **GitHub Pages**.

## Scopo del repository

Questo repository serve a:

1. contenere il codice sorgente del gioco;
2. compilare ed eseguire XTetris in locale come programma C;
3. pubblicare una versione giocabile nel browser tramite GitHub Actions + Emscripten.

In pratica, il progetto nasce come applicazione da console e simula una partita a Tetris basata su input testuale dell'utente.

## Cosa fa il gioco

All'avvio, XTetris mostra un menu iniziale con diverse modalità:

- **SinglePlayer**
- **Multiplayer vs persona**
- **Multiplayer vs PC**
- **Uscita**

Durante la partita il giocatore:

- sceglie un tetramino tra quelli disponibili;
- sceglie la rotazione del tetramino;
- sceglie la colonna in cui farlo cadere;
- cerca di completare righe per ottenere punti.

Il gioco mantiene uno stato interno della griglia, verifica se un pezzo può essere posizionato, elimina le righe complete e aggiorna il punteggio.

## Funzionalità principali

### 1. Gestione del piano di gioco

Il modulo `PianoDiGioco/` gestisce:

- la matrice di gioco;
- le celle vuote/piene;
- il posizionamento dei tetramini;
- la verifica delle collisioni;
- l'eliminazione delle righe complete;
- la condizione di fine partita quando si supera il limite superiore.

### 2. Gestione dei tetramini

Il modulo `Tetramino/` definisce:

- i 7 tipi di tetramino;
- le loro rotazioni;
- le dimensioni reali dei pezzi;
- la stampa dei pezzi a terminale;
- il set di pezzi disponibili durante la partita.

### 3. Modalità di gioco

Il file `main.c` gestisce il flusso principale del gioco:

- selezione modalità;
- inizializzazione giocatori;
- input utente;
- turni di gioco;
- calcolo del vincitore o della sconfitta.

### 4. Punteggio

Il punteggio viene assegnato in base al numero di righe eliminate in una singola mossa:

- **1 riga** → 1 punto
- **2 righe** → 3 punti
- **3 righe** → 6 punti
- **4 righe** → 12 punti

### 5. Tricky mode

È presente una modalità opzionale chiamata **tricky mode** in cui il tetramino non viene scelto manualmente, ma viene generato casualmente.

## Struttura del repository

```text
.
├── .github/workflows/        # Workflow GitHub Actions per build/deploy web
├── Elements/                 # Tipi di supporto, colori, rotazioni, utility
├── GameSetting/              # Menu, giocatori e logica di interazione
│   └── Player/
├── PianoDiGioco/             # Gestione della griglia e della logica di posizionamento
├── Tetramino/                # Definizione e gestione dei tetramini
├── CMakeLists.txt            # Configurazione build locale con CMake
└── main.c                    # Entry point del gioco
```

## Esecuzione locale

### Requisiti

- compilatore C
- CMake (opzionale ma consigliato)

### Build con CMake

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

Poi esegui il binario generato.

## Versione web

Il repository include anche un workflow GitHub Actions che:

1. installa **Emscripten**;
2. compila XTetris in **WebAssembly**;
3. genera una pagina HTML con interfaccia base;
4. pubblica il risultato su **GitHub Pages**.

Questa versione web è un adattamento del programma originale da terminale. Non è una riscrittura grafica completa del gioco: il motore resta quello testuale, ma viene eseguito nel browser.

## Limiti attuali della versione web

Poiché il progetto è nato per terminale:

- l'interazione è ancora basata su input sequenziali;
- il rendering è principalmente testuale;
- l'esperienza utente non è equivalente a una vera interfaccia grafica da browser.

In altre parole, la versione web serve soprattutto a:

- dimostrare il funzionamento del gioco;
- pubblicarlo online;
- rendere il progetto facilmente accessibile senza compilazione locale.

## Obiettivo complessivo del progetto

In sintesi, questo repo dovrebbe:

- implementare una versione testuale di Tetris in C;
- supportare partite singleplayer e multiplayer;
- gestire tetramini, rotazioni, punteggi e fine partita;
- poter essere eseguito sia localmente sia nel browser tramite GitHub Pages.

## Possibili evoluzioni future

Alcuni miglioramenti naturali del progetto potrebbero essere:

- una vera UI web grafica;
- controlli più naturali da tastiera;
- salvataggio punteggi;
- refactoring del codice C per separare meglio logica e interfaccia;
- test automatici per la logica di gioco.

---

Se vuoi, posso anche prepararti una seconda versione del README più:

- **accademica/formale**, oppure
- **da progetto open-source professionale**, con badge, sezione installazione, roadmap e contributor guide.

***
> [!NOTE]
> README.md genereted whit AI.
