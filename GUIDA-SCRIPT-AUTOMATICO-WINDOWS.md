# GUIDA SCRIPT AUTOMATICO WINDOWS - XTetris

Questa guida spiega come usare lo script automatico incluso nel repository per:

1. installare i prerequisiti principali;
2. forzare l'esecuzione con **PowerShell 7**;
3. preparare l'ambiente Windows;
4. compilare XTetris;
5. ottenere l'eseguibile pronto all'uso.

## Versione attuale degli script

```text
1.0.9k-STABLE
```

## File disponibili

Nel repository trovi:

- `installa-compila-windows.ps1` → script PowerShell principale consigliato
- `installa-compila-windows.bat` → wrapper batch principale consigliato
- `AVVIA-XTETRIS-WINDOWS.bat` → build automatica + avvio immediato del gioco
- `scripts/installa-compila-windows.ps1` → wrapper compatibile con la cartella `scripts`
- `scripts/installa-compila-windows.bat` → wrapper batch compatibile con la cartella `scripts`

---

## Cosa fa lo script

Lo script PowerShell prova a fare automaticamente queste operazioni:

- rileva se è stato aperto con **Windows PowerShell classico**;
- se serve, si rilancia automaticamente con **PowerShell 7**;
- se **PowerShell 7** non è installato, prova a installarlo con `winget`;
- mostra comunque il messaggio iniziale che avvisa se non sei amministratore;
- verifica che `winget` sia disponibile;
- installa **Git** se manca;
- installa **CMake** se manca;
- installa **MSYS2** se manca;
- installa tramite MSYS2 i pacchetti di build:
  - GCC
  - CMake
  - Ninja
- configura la build del progetto con CMake;
- compila XTetris;
- produce `build\\XTetris.exe`;
- crea automaticamente in root il file `AVVIA GIOCO.bat`;
- alla fine chiede: **"Vuoi avviare il gioco?"**

---

## Come usarlo

### Metodo 1 - Da PowerShell

Apri **PowerShell** o **Windows Terminal** nella cartella del repository e lancia:

```powershell
powershell -ExecutionPolicy Bypass -File .\installa-compila-windows.ps1
```

> Anche se parti da Windows PowerShell classico, lo script proverà a spostarsi automaticamente su **PowerShell 7**.

### Metodo 2 - Avvio con doppio click

Puoi provare anche con:

- `installa-compila-windows.bat`

Oppure, se vuoi compilare e avviare subito il gioco:

- `AVVIA-XTETRIS-WINDOWS.bat`

Questi file richiamano automaticamente **PowerShell 7 (`pwsh`)**. Se `pwsh` non è installato, tentano prima di installarlo.

---

## Avvio automatico del gioco dopo la build

Se vuoi compilare e poi avviare subito XTetris senza domanda finale:

```powershell
powershell -ExecutionPolicy Bypass -File .\installa-compila-windows.ps1 -RunAfterBuild
```

---

## File generato automaticamente

Se la compilazione va a buon fine, lo script crea questo file nella root del progetto:

```text
AVVIA GIOCO.bat
```

Questo launcher serve per avviare rapidamente il gioco compilato in seguito, senza rifare tutto il setup.

---

## Dove trovo l'eseguibile

Al termine, l'eseguibile si troverà in:

```text
build\XTetris.exe
```

---

## Limiti dello script

Lo script automatizza molto, ma ci sono alcune dipendenze di sistema che devono già funzionare correttamente:

### 1. `winget` deve esistere

Se `winget` non è installato, lo script non può installare automaticamente PowerShell 7 / Git / CMake / MSYS2.

In quel caso installa:

- **App Installer** dal Microsoft Store

### 2. Potrebbero comparire prompt di conferma

Anche senza auto-elevazione ad amministratore, alcuni installer possono chiedere conferme, a seconda della configurazione del PC.

### 3. La prima installazione può richiedere tempo

MSYS2 e i pacchetti di build non sono piccoli: la prima esecuzione può durare diversi minuti.

---

## Se qualcosa va storto

### Errore su `winget`

Installa o aggiorna App Installer.

### Errore su PowerShell 7

Rilancia lo script. Se necessario installa manualmente **PowerShell 7** e poi riprova.

### Errore su Git/CMake/MSYS2

Rilancia lo script da una nuova finestra PowerShell.

### Errore durante la build

Controlla che il repository sia completo e che `CMakeLists.txt` sia presente nella root.

---

## Uso consigliato

Per la maggior parte degli utenti Windows, il flusso più semplice è:

1. scaricare o clonare il repository;
2. aprire la cartella del progetto;
3. fare doppio click su:

```text
installa-compila-windows.bat
```

oppure, se vuoi compilare e lanciare subito il gioco:

```text
AVVIA-XTETRIS-WINDOWS.bat
```

4. in alternativa, dopo una build riuscita, usare:

```text
AVVIA GIOCO.bat
```

---

## In sintesi

Se vuoi evitare setup manuale, il file principale da usare è:

```text
installa-compila-windows.ps1
```

Se vuoi il launcher più comodo da doppio click:

```text
installa-compila-windows.bat
```

Se vuoi compilare e avviare subito:

```text
AVVIA-XTETRIS-WINDOWS.bat
```

È il modo più vicino possibile a un install/build automatico per usare XTetris originale su Windows.
***
> [!NOTE]
> File genereted whit [Arena AI](https://arena.ai/)
<!-- File Generato con Arena AI (https://arena.ai/) -->
