<!-- immagine logo generata con gemini (google) -->
<div align="center">
  <a href="https://piboh.github.io/XTetris/">
     <img width="300" height="300" alt="xtetrisimage_nobg" src="https://github.com/PiBOH/XTetris/blob/main/piboh-images/xtetrisimage_nobg.png" />


[<img src="https://img.shields.io/github/v/release/PiBOH/XTetris?style=for-the-badge&logo=abdownloadmanager&label=Download%20the%20latest%20stable%20Version&labelColor=121222&cacheSeconds=60&link=https%3A%2F%2Fgithub.com%2FPiBOH%2FXTetris%2Freleases%2Flatest%2Fdownload%2FXTetris.zip" height="99">](https://github.com/PiBOH/XTetris/releases/latest/download/XTetris.zip)

<!-- [![Deploy GitHub Pages](https://github.com/PiBOH/XTetris/actions/workflows/deploy.yml/badge.svg)](https://github.com/PiBOH/XTetris/actions/workflows/deploy.yml) -->
[![Gtihub Pages State](https://img.shields.io/website?url=https%3A%2F%2Fpiboh.github.io%2FXTetris%2F&up_message=online&up_color=009736&down_message=offline&down_color=ff0001&style=flat&logo=googleearth&label=Github%20Pages&labelColor=121222&cacheSeconds=300&link=https%3A%2F%2Fpiboh.github.io%2FXTetris%2F)](https://piboh.github.io/XTetris) <!-- github pages -->
[![GitHub Downloads (all assets, all releases)](https://img.shields.io/github/downloads/PiBOH/XTetris/total?logo=GitHub&cacheSeconds=60)](https://github.com/PiBOH/XTetris/releases/)
[![GitHub Downloads (all assets, latest release)](https://img.shields.io/github/downloads/PiBOH/XTetris/latest/total)](https://github.com/PiBOH/XTetris/releases/latest)
[![License](https://img.shields.io/github/license/PiBOH/XTetris)](LICENSE)
[![Last Commit](https://img.shields.io/github/last-commit/PiBOH/XTetris)](https://github.com/PiBOH/XTetris/commits/main)


<!-- [![GitHub Release](https://img.shields.io/github/v/release/PiBOH/XTetris?display_name=tag&style=flat-square&logo=google%20gemini&logoColor=e5e6e8&label=Stable%20Release%20Version&labelColor=121212&cacheSeconds=60)](https://github.com/PiBOH/XTetris/blob/main/piboh-script/version.txt) -->

</div>

## Uso rapido

### Windows
Esegui il file `MENU-XTETRIS-WINDOWS.bat` e scegli tra le opzioni disponibili inserendo il loro numero di elenco:

1 - Installa prerequisiti e compila XTetris

2 - Compila e avvia subito XTetris

3 - Avvia il gioco gia compilato

4 - Disinstalla dipendenze / rimuovi build e file compilati di XTetris

5 - Apri una guida in Notepad++

6 - Visualizza CHANGELOG.md

7 - Controlla integrita del repository (Preview)

8 - Pulisci log e cache (Preview)

9 - Esci


> [!NOTE]
> Il repository include anche **Notepad++ Portable**, utile per aprire e leggere i file **Markdown** del progetto, con il plugin **NppMarkdownPanel** integrato per la preview Markdown.

Le dipendenze gestite automaticamente vengono installate nella cartella `piboh-temp/` del progetto. **PowerShell 7** viene sempre installato nel percorso predefinito, ma se in `piboh-portable/PowerShell-7/` è presente una copia portable di `pwsh.exe`, gli script usano quella con priorità assoluta. **Git** non viene gestito dagli script automatici. Per rimuovere le dipendenze non più necessarie si basta selezionare l'apposita opzione dal menu.

La rimozione opzionale di XTetris elimina la cartella `build`, gli eventuali file compilati presenti nella root del progetto e il launcher generato `AVVIA GIOCO.bat`.

I log degli script vengono salvati in:

- `piboh-script/log/`

La versione corrente degli script è salvata in:

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

Il repository pubblica anche una versione browser tramite **[GitHub Pages](https://piboh.github.io/XTetris/)**.

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
├── piboh-images/
|   ├── xterisimage.jpeg
|   └── xterisimage_nobg.png
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
├── piboh-images/
|   ├── xterisimage.jpeg
|   └── xterisimage_nobg.png
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

<!-- File Generato con Arena AI (https://arena.ai/) e riadattato da [PiBOH](https://piboh.github.io) per renderlo più "umano" e comprensibile dalle persone. -->
