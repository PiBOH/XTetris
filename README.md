# XTetris

[![Deploy GitHub Pages](https://github.com/PiBOH/XTetris/actions/workflows/deploy.yml/badge.svg)](https://github.com/PiBOH/XTetris/actions/workflows/deploy.yml)
[![GitHub Pages](https://img.shields.io/badge/GitHub%20Pages-online-blue)](https://piboh.github.io/XTetris/)
![GitHub Downloads (all assets, latest release)](https://img.shields.io/github/downloads/PiBOH/XTetris/latest/total)
[![License](https://img.shields.io/github/license/PiBOH/XTetris)](LICENSE)
[![Last Commit](https://img.shields.io/github/last-commit/PiBOH/XTetris)](https://github.com/PiBOH/XTetris/commits/main)
[![Top Language](https://img.shields.io/github/languages/top/PiBOH/XTetris)](https://github.com/PiBOH/XTetris)

XTetris è un gioco **Tetris testuale in C**.

**Versione corrente degli script:** `3.0.45` (letta da `piboh-script/version.txt`)

## Uso rapido

### Windows
Esegui uno di questi file:

- `MENU-XTETRIS-WINDOWS.bat`
- `piboh-script/installa-compila-windows.bat`
- `AVVIA GIOCO.bat` (generato automaticamente dopo una build riuscita)

Dal menu puoi anche:

- aprire il **CHANGELOG**
- controllare l'integrità dei file del repository
- aprire le guide con **Notepad++ Portable**

Il repository include anche **Notepad++ Portable**, utile per aprire e leggere i file **Markdown** del progetto, con il plugin **NppMarkdownPanel** integrato per la preview Markdown.

Se in `piboh-portable/PowerShell-7/` è presente una copia **portable** di PowerShell 7 (`pwsh.exe`), gli script la useranno con priorità rispetto a quella installata nel sistema.

Per rimuovere in seguito le dipendenze installate, usa:

- `piboh-script/disinstalla-dipendenze-windows.bat`

Le dipendenze gestite automaticamente vengono installate nella cartella `piboh-temp/` del progetto. **PowerShell 7** viene sempre installato nel percorso predefinito, ma se in `piboh-portable/PowerShell-7/` è presente una copia portable di `pwsh.exe`, gli script usano quella con priorità assoluta. **Git** non viene gestito dagli script automatici.

La rimozione opzionale di XTetris elimina la cartella `build`, gli eventuali file compilati presenti nella root del progetto e il launcher generato `AVVIA GIOCO.bat`.

I log degli script vengono salvati in:

- `piboh-script/log/`

La versione corrente degli script è centralizzata in:

- `piboh-script/version.txt`

### Build manuale
```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## Guide

- [Guida Windows](guide/GUIDA-WINDOWS.md)
- [Guida rapida](guide/GUIDA-WINDOWS-RAPIDA.md)
- [Guida script automatico](guide/GUIDA-SCRIPT-AUTOMATICO-WINDOWS.md)
- [Guida MSYS2](guide/GUIDA-MSYS2.md)
- [Guida CLion](guide/GUIDA-CLION-WINDOWS.md)
- [Guida VS Code](guide/GUIDA-VSCODE-WINDOWS.md)
- [Changelog](CHANGELOG.md)

## Web

Il repository pubblica anche una versione browser tramite **GitHub Pages**.

## Struttura del repository

<details>
<summary>Apri per vedere la struttura completa del repository</summary>

### Struttura base (senza build)

```text
XTetris/
├── .github/
│   └── workflows/
├── .idea/
├── Elements/
│   ├── boolType.h
│   ├── color_codes.h
│   ├── colori.h
│   ├── exit_modes.h
│   ├── rotazioni.h
│   └── string.h
├── GameSetting/
│   ├── Player/
│   │   ├── player.c
│   │   └── player.h
│   ├── menus.c
│   └── menus.h
├── PianoDiGioco/
│   ├── pianodigioco.c
│   └── pianodigioco.h
├── Tetramino/
│   ├── tetramino.c
│   └── tetramino.h
├── guide/
│   ├── GUIDA-CLION-WINDOWS.md
│   ├── GUIDA-MSYS2.md
│   ├── GUIDA-SCRIPT-AUTOMATICO-WINDOWS.md
│   ├── GUIDA-VSCODE-WINDOWS.md
│   ├── GUIDA-WINDOWS-RAPIDA.md
│   └── GUIDA-WINDOWS.md
├── piboh-portable/
│   ├── Notepad++Portable/
│   │   ├── plugins/NppMarkdownPanel/
│   │   └── shortcuts.xml
│   └── PowerShell-7/
├── piboh-script/
│   ├── apri-guide-windows.bat
│   ├── disinstalla-dipendenze-windows.bat
│   ├── disinstalla-dipendenze-windows.ps1
│   ├── installa-compila-windows.bat
│   ├── installa-compila-windows.ps1
│   ├── log/
│   ├── verifica-integrita-windows.bat
│   └── version.txt
├── .gitignore
├── CHANGELOG.md
├── CMakeLists.txt
├── MENU-XTETRIS-WINDOWS.bat
└── main.c
```

### Struttura tipica dopo la compilazione

```text
XTetris/
├── build/
│   ├── XTetris.exe
│   └── ...
├── cmake-build-debug/
├── AVVIA GIOCO.bat
├── main.o
├── menus.o
├── player.o
├── tetramino.o
├── CHANGELOG.md
├── MENU-XTETRIS-WINDOWS.bat
├── guide/
├── piboh-portable/
│   ├── Notepad++Portable/
│   │   ├── plugins/NppMarkdownPanel/
│   │   └── shortcuts.xml
│   └── PowerShell-7/
├── piboh-script/
└── ...
```

</details>

## Thanks to

- [AlexGiulioBerton](https://github.com/AlexGiulioBerton)

<!-- File Generato con Arena AI (https://arena.ai/) -->
