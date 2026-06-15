# GUIDA SCRIPT AUTOMATICO WINDOWS - XTetris

Questa guida spiega come usare lo script automatico incluso nel repository per:

1. installare i prerequisiti principali;
2. forzare l'esecuzione con **PowerShell 7**;
3. preparare l'ambiente Windows;
4. compilare XTetris;
5. ottenere l'eseguibile pronto all'uso.

## Versioni attuali degli script

```text
Menu: 1.0.23.2
Installatore: 1.0.9k
Disinstallatore: 1.0.22
```

## File disponibili

Nel repository trovi:

- `MENU-XTETRIS-WINDOWS.bat` → menu principale Windows, con fallback automatico se manca `AVVIA-XTETRIS-WINDOWS.bat`
- `AVVIA-XTETRIS-WINDOWS.bat` → build automatica + avvio immediato del gioco
- `piboh-script/installa-compila-windows.ps1` → script PowerShell principale consigliato
- `piboh-script/installa-compila-windows.bat` → launcher batch di installazione e compilazione
- `piboh-script/disinstalla-dipendenze-windows.ps1` → script PowerShell di disinstallazione
- `piboh-script/disinstalla-dipendenze-windows.bat` → launcher batch di disinstallazione
- `piboh-portable/Notepad++Portable/` → copia portable di Notepad++ inclusa nel repository

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
- usa **Notepad++ Portable** integrato nel repository per aprire i file Markdown;
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
powershell -ExecutionPolicy Bypass -File .\piboh-script\installa-compila-windows.ps1
```

> Anche se parti da Windows PowerShell classico, lo script proverà a spostarsi automaticamente su **PowerShell 7**.

### Metodo 2 - Avvio con doppio click

Puoi provare anche con:

- `MENU-XTETRIS-WINDOWS.bat`
- `piboh-script/installa-compila-windows.bat`

Oppure, se vuoi compilare e avviare subito il gioco:

- `AVVIA-XTETRIS-WINDOWS.bat`

Questi file richiamano automaticamente **PowerShell 7 (`pwsh`)**. Se `pwsh` non è installato, tentano prima di installarlo. Le opzioni di avvio del gioco dal menu vengono eseguite in una finestra separata e, alla chiusura del gioco, il controllo torna al menu principale. Inoltre il menu prova a pulire l'input residuo della console prima di tornare operativo.

---

## Avvio automatico del gioco dopo la build

Se vuoi compilare e poi avviare subito XTetris senza domanda finale:

```powershell
powershell -ExecutionPolicy Bypass -File .\piboh-script\installa-compila-windows.ps1 -RunAfterBuild
```

---

## File generato automaticamente

Se la compilazione va a buon fine, lo script crea questo file nella root del progetto:

```text
AVVIA GIOCO.bat
```

Questo launcher serve per avviare rapidamente il gioco compilato in seguito, senza rifare tutto il setup.

## Disinstallazione

Per rimuovere le dipendenze installate dagli script puoi usare:

```text
piboh-script/disinstalla-dipendenze-windows.bat
```

Lo script di disinstallazione rimuove solo le dipendenze che **non erano già presenti nel sistema** e che sono state effettivamente installate dagli script automatici (ad esempio **PowerShell 7**, **Git**, **CMake** e **MSYS2**). Se una dipendenza era già installata prima dell'esecuzione del menu o dello script di installazione, non viene rimossa. **Notepad++ Portable** non viene rimosso. Per XTetris, la disinstallazione opzionale rimuove la cartella `build`, gli eventuali file compilati presenti nella root del progetto e il launcher generato `AVVIA GIOCO.bat`, ma **non** elimina l'intero repository.

---

## Log

Gli script creano automaticamente la cartella:

```text
piboh-script/log/
```

Dentro questa cartella vengono salvati i log dei launcher batch e i transcript dei principali script PowerShell.

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
MENU-XTETRIS-WINDOWS.bat
```

oppure, se vuoi andare direttamente all'installazione:

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

## Guide collegate

- [Guida completa Windows](GUIDA-WINDOWS.md)
- [Guida rapida Windows](GUIDA-WINDOWS-RAPIDA.md)
- [Guida MSYS2](GUIDA-MSYS2.md)
- [Guida CLion su Windows](GUIDA-CLION-WINDOWS.md)
- [Guida VS Code su Windows](GUIDA-VSCODE-WINDOWS.md)
- **Guida script automatico Windows** (guida corrente)

> [!NOTE]
>
> File genereted whit [Arena AI](https://arena.ai).
