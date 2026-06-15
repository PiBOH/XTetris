# GUIDA WINDOWS - XTetris originale da terminale

Questa guida spiega come usare **XTetris nella sua forma originale**, cioè come **programma C da terminale su Windows**, senza GitHub Pages e senza la versione WebAssembly.

> In breve: il progetto nasce come gioco **testuale**. Si compila in C e si esegue da console, interagendo con il programma tramite input numerici e testuali.

---

## 1. Cos'è XTetris in origine

XTetris è una variante di **Tetris da terminale** scritta in **C**.

Il gioco:

- mostra un menu iniziale;
- permette di giocare in **single player**;
- permette di giocare in **multiplayer contro un'altra persona**;
- permette di giocare in **multiplayer contro il PC**;
- usa input da tastiera tramite console;
- stampa la griglia, i tetramini, i punteggi e gli stati di vittoria/sconfitta direttamente nel terminale.

Non è un gioco grafico con finestre, mouse o bottoni: va usato in **Prompt dei comandi**, **PowerShell** o **Windows Terminal**.

---

## 2. Cosa ti serve su Windows

Per eseguirlo in locale ti consiglio di usare:

- **Windows Terminal** oppure **PowerShell**
- **Git** (opzionale, se devi clonare il repository)
- **CMake**
- **MinGW-w64 / GCC**

### Configurazione consigliata

La combinazione più semplice e compatibile è:

- **Git for Windows**
- **CMake**
- **MSYS2 + MinGW-w64 GCC**

> Consiglio importante: per questo progetto è meglio usare **GCC/MinGW** invece di **MSVC/Visual Studio compiler**, perché il codice è chiaramente pensato per una toolchain C classica stile GCC/CMake.

---

## 3. Scaricare il progetto

Se non hai ancora i file, apri PowerShell o Windows Terminal e fai:

```powershell
git clone https://github.com/PiBOH/XTetris.git
cd XTetris
```

Se invece hai già scaricato il repository come ZIP, estrailo e apri il terminale nella cartella del progetto.

---

## 4. Metodo consigliato: compilazione con CMake

Il repository contiene già un file `CMakeLists.txt`, quindi il modo più pulito per compilare è usare **CMake**.

### 4.1 Crea una cartella di build

Da terminale, dentro la root del progetto:

```powershell
mkdir build
cd build
```

### 4.2 Genera i file di build

Se hai installato MinGW/GCC correttamente:

```powershell
cmake .. -G "MinGW Makefiles"
```

### 4.3 Compila

```powershell
cmake --build .
```

Se tutto va bene, otterrai un eseguibile chiamato:

```text
XTetris.exe
```

oppure equivalente nella cartella `build`.

---

## 5. Metodo alternativo: compilazione diretta con GCC

Se preferisci compilare senza CMake, dalla root del progetto puoi usare un comando simile a questo:

```powershell
gcc main.c Tetramino/tetramino.c PianoDiGioco/pianodigioco.c GameSetting/menus.c GameSetting/Player/player.c -o XTetris.exe
```

Se necessario, assicurati di eseguire il comando in un ambiente dove `gcc` è disponibile nel `PATH`.

> Se usi **MSYS2 MinGW**, apri il terminale giusto di MinGW e lancia il comando lì.

---

## 6. Come avviare il gioco

Dopo la compilazione, esegui il programma da terminale.

Se sei nella cartella `build`:

```powershell
.\XTetris.exe
```

Oppure, se hai compilato nella root:

```powershell
.\XTetris.exe
```

> Importante: **non** conviene avviarlo con doppio click dall'Esplora file, perché il programma è interattivo da console e la finestra potrebbe chiudersi subito o comportarsi male. Avvialo sempre da terminale.

---

## 7. Come si usa il gioco

Appena parte, XTetris mostra il menu iniziale:

- `1` → SinglePlayer
- `2` → MultiPlayer (vs Person)
- `3` → MultiPlayer (vs PC)
- `4` → Esci

Tu inserisci il numero e premi **Invio**.

### 7.1 Tricky mode

Dopo la scelta della modalità, il gioco chiede se vuoi entrare nella **tricky mode**.

Di solito:

- `1` = Sì
- `0` = No

Nella tricky mode il tetramino può essere scelto casualmente invece che manualmente.

### 7.2 Nome del giocatore

In modalità single player e multiplayer il gioco chiede il nome del giocatore.

Scrivi il nome e premi **Invio**.

### 7.3 Scelta del tetramino

Durante la partita il gioco può chiederti:

- se vuoi vedere tutti i tetramini disponibili;
- quale tetramino scegliere;
- quale rotazione applicare.

In pratica il flusso tipico è:

1. scegli il tetramino tramite **ID**;
2. scegli la rotazione tramite **ID**;
3. scegli la colonna in cui farlo cadere.

### 7.4 Scelta della colonna

Il gioco ti chiede in quale colonna vuoi posizionare il lato destro del tetramino.

Le colonne valide sono:

```text
0 1 2 3 4 5 6 7 8 9
```

Inserisci un numero e premi **Invio**.

---

## 8. Modalità disponibili

### SinglePlayer

Giochi da solo e cerchi di fare più punti possibile eliminando righe.

### Multiplayer vs Person

Due giocatori umani si alternano nello stesso terminale.

### Multiplayer vs PC

Giochi contro il computer.

---

## 9. Sistema di punteggio

Il progetto assegna punti in base al numero di righe eliminate in una sola mossa:

- **1 riga** → 1 punto
- **2 righe** → 3 punti
- **3 righe** → 6 punti
- **4 righe** → 12 punti

---

## 10. Fine partita

La partita termina quando:

- si supera il limite superiore della matrice di gioco;
- finiscono i tetramini disponibili;
- uno dei giocatori perde o l'altro vince, a seconda della modalità.

Il gioco stampa a terminale messaggi di:

- vittoria;
- sconfitta;
- fine partita;
- punteggio dei giocatori.

---

## 11. Consigli pratici per Windows

### Usa un terminale moderno

Ti consiglio:

- **Windows Terminal**
- oppure **PowerShell**

perché il gioco usa molta stampa testuale e alcuni codici colore ANSI.

### Se i colori non si vedono bene

Non è un problema grave: il gioco resta utilizzabile anche se alcuni colori non vengono renderizzati perfettamente.

### Se la finestra sembra "bloccata"

Il programma originale contiene dei piccoli **delay artificiali**. Quindi a volte sembra fermo per un attimo mentre in realtà sta solo aspettando o stampando il turno successivo.

---

## 12. Problemi comuni

### Errore: `gcc` non trovato

Significa che GCC non è installato o non è nel `PATH`.

Soluzione:

- installa **MSYS2/MinGW-w64**;
- apri il terminale MinGW corretto;
- verifica con:

```powershell
gcc --version
```

### Errore: `cmake` non trovato

Installa CMake e verifica con:

```powershell
cmake --version
```

### Il programma parte e si chiude subito

Probabilmente lo hai aperto con doppio click.

Soluzione:

- apri un terminale;
- vai nella cartella dell'eseguibile;
- lancialo con `./XTetris.exe` o `.\XTetris.exe`.

### L'output è disallineato

Può succedere se usi una console con font o dimensioni non adatti.

Soluzione:

- usa un font monospaziato;
- allarga la finestra del terminale.

---

## 13. Cartelle principali del progetto

```text
XTetris/
├── Elements/                # Tipi di supporto, colori, rotazioni, utility
├── GameSetting/             # Menu e logica di gioco
│   └── Player/              # Gestione giocatori
├── PianoDiGioco/            # Griglia e logica di posizionamento
├── Tetramino/               # Definizione dei tetramini
├── CMakeLists.txt           # Build con CMake
└── main.c                   # Entry point del programma
```

---

## 14. Flusso rapido consigliato

Se vuoi la versione più semplice possibile su Windows:

1. installa **Git**, **CMake**, **MinGW-w64**;
2. clona il repo;
3. apri il terminale nella cartella del progetto;
4. esegui:

```powershell
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
cmake --build .
.\XTetris.exe
```

---

## 15. In sintesi

La versione originale di XTetris su Windows si usa così:

- si compila come normale programma C;
- si avvia da terminale;
- si gioca inserendo numeri e testi richiesti dal menu;
- non richiede browser, GitHub Pages o WebAssembly.

Se vuoi, nel prossimo messaggio posso anche prepararti una seconda guida:

- **GUIDA-WINDOWS-RAPIDA.md** super corta, oppure
- una guida con **screenshots/step numerati** per utenti non tecnici.

***
> [!NOTE]
> Queste istruzioni sono AI Generated.
