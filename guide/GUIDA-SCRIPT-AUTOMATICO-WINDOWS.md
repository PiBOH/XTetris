# GUIDA SCRIPT AUTOMATICO WINDOWS - XTetris

Questa guida spiega come usare lo script automatico incluso nel repository per:

1. installare i prerequisiti principali;
2. forzare l'esecuzione con **PowerShell 7**;
3. preparare l'ambiente Windows;
4. compilare XTetris;
5. ottenere l'eseguibile pronto all'uso.

## Versioni attuali degli script

```text
Menu: 3.0.15
Installatore: 3.0.15
Disinstallatore: 3.0.15
Guide launcher: 3.0.15
Integrity check: 3.0.15
```

## File disponibili

Nel repository trovi (versione corrente letta da `piboh-script/version.txt` = `3.0.15`):

- `MENU-XTETRIS-WINDOWS.bat` → pre-menu principale Windows, con accesso a installazione, avvio, guide, changelog e controllo integrità
- `piboh-script/installa-compila-windows.ps1` → script PowerShell principale consigliato
- `piboh-script/installa-compila-windows.bat` → launcher batch di installazione e compilazione
- `piboh-script/disinstalla-dipendenze-windows.ps1` → script PowerShell di disinstallazione
- `piboh-script/disinstalla-dipendenze-windows.bat` → launcher batch di disinstallazione
- `piboh-script/apri-guide-windows.bat` → menu dedicato per aprire le guide in Notepad++
- `piboh-script/verifica-integrita-windows.bat` → controllo integrità del repository
- `piboh-portable/Notepad++Portable/` → copia portable di Notepad++ inclusa nel repository
- `piboh-portable/Notepad++Portable/plugins/NppMarkdownPanel/` → plugin NppMarkdownPanel integrato per la preview Markdown
- `CHANGELOG.md` → storico sintetico delle modifiche
- `AVVIA GIOCO.bat` → launcher generato automaticamente dopo una build riuscita

---

## Cosa fa l'installatore

Lo script PowerShell di installazione prova a fare automaticamente queste operazioni:

- permette di scegliere se installare le dipendenze in `piboh-temp/` oppure nel percorso predefinito;
- mantiene **PowerShell 7** sempre nel percorso predefinito;
- tratta **Git** come componente opzionale;
- rileva se è stato aperto con **Windows PowerShell classico**;
- se serve, si rilancia automaticamente con **PowerShell 7**;
- se **PowerShell 7** non è installato, prova a installarlo con `winget` in modalità silenziosa;
- mostra comunque il messaggio iniziale che avvisa se non sei amministratore;
- verifica che `winget` sia disponibile;
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

### Metodo 2 - Da menu

Usa:

- `MENU-XTETRIS-WINDOWS.bat`

Oppure direttamente:

- `piboh-script/installa-compila-windows.bat`

---

## Visualizzazione guide e changelog

Dal menu principale puoi:

- aprire una guida in Notepad++
- aprire direttamente `CHANGELOG.md`

La priorità è:

1. **Notepad++ Portable** nel repository
2. eventuale **Notepad++ di sistema** se disponibile

Quando apri una guida o il changelog, il launcher prova anche ad attivare automaticamente la preview del plugin **NppMarkdownPanel** (se presente nella copia portable).

---

## Disinstallazione

Per rimuovere le dipendenze installate dagli script puoi usare:

```text
piboh-script/disinstalla-dipendenze-windows.bat
```

Lo script di disinstallazione rimuove solo le dipendenze che **non erano già presenti nel sistema** e che sono state effettivamente installate dagli script automatici (ad esempio **PowerShell 7**, **Git**, **CMake** e **MSYS2**). Se una dipendenza era già installata prima dell'esecuzione del menu o dello script di installazione, non viene rimossa.

**Notepad++ Portable** non viene rimosso.

Per XTetris, la disinstallazione opzionale rimuove:

- la cartella `build`
- gli eventuali file compilati presenti nella root del progetto
- il launcher generato `AVVIA GIOCO.bat`

ma **non** elimina l'intero repository.

---

## Controllo integrità

Dal menu principale puoi eseguire un controllo dei file principali del repository tramite:

```text
piboh-script/verifica-integrita-windows.bat
```

Il controllo verifica anche la presenza di:

- `piboh-script/version.txt`
- `piboh-portable/Notepad++Portable/shortcuts.xml`
- `piboh-portable/Notepad++Portable/plugins/NppMarkdownPanel/NppMarkdownPanel.dll`

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

## Se qualcosa va storto

### Errore su `winget`

Installa o aggiorna App Installer.

### Errore su PowerShell 7

Rilancia lo script. Se necessario installa manualmente **PowerShell 7** e poi riprova.

### Errore durante la build

Controlla che il repository sia completo e che `CMakeLists.txt` sia presente nella root.

---

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
