# CHANGELOG

## 3.0.3
- Aggiornate tutte le versioni dei file script e dei riferimenti documentali alla versione `3.0.3`.
- Installatore migliorato: scelta del percorso dipendenze, Git opzionale, uso di `--silent` e metadati delle installazioni.
- Disinstallatore migliorato: rimozione silenziosa dei pacchetti installati dallo script usando uninstaller nascosti o winget silenzioso.

## 3.0.2
- Aggiornate tutte le versioni degli script e dei riferimenti documentali alla versione `3.0.2`.
- Rimossa la dipendenza residua da `AVVIA-XTETRIS-WINDOWS.bat` nella documentazione e nei flussi reali di utilizzo.
- Avviata pulizia finale del repository e delle versioni mostrate all'utente.

## 3.0.1
- Allineate tutte le versioni degli script, launcher e strumenti ausiliari alla versione `3.0.1`.
- Il menu non dipende più da `AVVIA-XTETRIS-WINDOWS.bat`: usa direttamente l'installatore oppure il launcher generato `AVVIA GIOCO.bat`.
- Aggiunta scelta del percorso di installazione delle dipendenze (`piboh-temp` oppure percorso predefinito), con **PowerShell 7** sempre nel percorso predefinito.
- **Git** reso opzionale nell'installazione.
- Aggiunte opzioni da menu per aprire il **CHANGELOG** e controllare l'integrità del repository.
- Aggiornata la visualizzazione del gioco per lasciare a schermo soprattutto XTetris al momento dell'avvio.

## 1.0.25
- Aggiornato `MENU-XTETRIS-WINDOWS.bat` alla dicitura **XTetris Windows Pre-Menu**.
- Aggiunta opzione per visualizzare `CHANGELOG.md` dal menu.
- Aggiunta opzione per controllare l'integrita del repository.
- Aggiunto `piboh-script/verifica-integrita-windows.bat`.
- Aggiornato `piboh-script/apri-guide-windows.bat` alla versione 1.0.25.
- Migliorata la gestione di guide e changelog tramite Notepad++ portable o quello disponibile nel sistema.

## 1.0.24
- Sistemata la selezione delle opzioni nel menu principale con input manuale.
- Sistemato il launcher dedicato per le guide.
- Stabilizzato il ritorno al menu dopo la chiusura delle finestre esterne.

## 1.0.23
- Introdotto `piboh-script/apri-guide-windows.bat` per l'apertura delle guide.
- Separata la gestione delle guide dal menu principale.
- Aggiornato il disinstallatore per rimuovere solo build, file compilati e `AVVIA GIOCO.bat`.
- Confermato che `piboh-portable/Notepad++Portable` non viene rimosso.

## 1.0.22
- Il menu e i sotto-menu usano pulizia dell'input residuo.
- Il disinstallatore rimuove solo le dipendenze installate dagli script.
- Aggiunta la cartella `piboh-script/log/` per i log.

## 1.0.21
- Introdotto `MENU-XTETRIS-WINDOWS.bat` come menu principale.
- Aggiunta la gestione delle guide con Notepad++.
- Aggiunte versioni distinte per menu, installatore e disinstallatore.

## 1.0.19r / 1.0.9k / 1.0.22
- Allineate le versioni intermedie degli script.
- Migliorata la gestione di PowerShell 7 e dei launcher batch.

## Modifiche funzionali precedenti
- Creati script Windows per installazione e compilazione automatica.
- Creata la guida completa Windows, guida rapida, guida MSYS2, guida CLion, guida VS Code e guida script automatico.
- Spostate le guide nella cartella `guide/`.
- Spostati gli script nella cartella `piboh-script/`.
- Integrata copia **Notepad++ Portable** in `piboh-portable/Notepad++Portable/`.
- Aggiunta la pubblicazione web tramite GitHub Pages / WebAssembly.
- Creato `AVVIA GIOCO.bat` generato automaticamente dopo una build riuscita.
- Aggiunti log e tracciamento dei pacchetti installati dagli script.
- Aggiunta disinstallazione controllata di dipendenze e artefatti compilati.
- README semplificato con badge, struttura del repository e sezione thanks.
- Collegamento tra tutte le guide e nota finale Arena AI.

> [!NOTE]
>
> File genereted whit [Arena AI](https://arena.ai).
