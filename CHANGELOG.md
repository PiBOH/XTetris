# CHANGELOG

## 3.1.19
- Corretto `piboh-script/verifica-integrita-windows.bat`: il riepilogo finale usa ora una struttura batch compatibile e l'opzione 7 non dovrebbe mandare più in crash il menu.
- Aggiornato `piboh-script/pulisci-log-cache-windows.bat`: ora svuota tutti i file dentro `piboh-script/log/`, rimuove `piboh-temp/` ed elimina nel repository gli altri file che contengono `cache` nel nome, escludendo lo script stesso.
- Ripulito `README.md` rimuovendo sezioni ridondanti e lasciando una struttura più compatta e coerente con l'uso reale del repository.
- Aggiornato `piboh-script/version.txt` alla versione `3.1.19`.

## 3.1.13
- Rimosso il messaggio duplicato sul rilevamento di PowerShell 7 Portable dal launcher batch: il rilevamento viene mostrato una sola volta dallo script PowerShell principale.
- Aggiunta l'opzione menu `Pulisci log e cache` con il nuovo file `piboh-script/pulisci-log-cache-windows.bat`, che pulisce i file `.log` e la cartella `piboh-temp/`.
- Reso silenzioso il controllo preliminare di MSYS2 nello script di installazione, evitando il messaggio di errore transitorio quando MSYS2 non è ancora disponibile nel percorso atteso.
- Aggiornato `piboh-script/version.txt` alla versione `3.1.13`.

## 3.0.45
- Aggiornato `piboh-script/version.txt` alla versione `3.0.45`.
- Bug Fix generale
- Riallineati `README.md` e `guide/GUIDA-SCRIPT-AUTOMATICO-WINDOWS.md` alla versione centrale corrente.
- Consolidato il versionamento dopo l'eccezione `3.0.44.1` e ripristinato l'incremento normale.

## 3.0.38
- Aggiornato `piboh-script/version.txt` alla versione `3.0.38`.
- Ripristinata e consolidata l'installazione delle dipendenze in `piboh-temp/`.
- Confermata la correzione dell'installer per MSYS2/CMake con ricerca più robusta e controllo di usabilità meno fragile.
- Riallineati `README.md` e `guide/GUIDA-SCRIPT-AUTOMATICO-WINDOWS.md` alla nuova versione centrale.

## 3.0.33
- Aggiornato `piboh-script/version.txt` alla versione `3.0.33`.
- Confermata la correzione dell'installatore per MSYS2: se il pacchetto risulta installato ma non è utilizzabile nel percorso atteso, viene tentata una reinstallazione/repair con `--force`.
- Riallineati `README.md` e `guide/GUIDA-SCRIPT-AUTOMATICO-WINDOWS.md` alla nuova versione centrale.

## 3.0.24
- Aggiornato `piboh-script/version.txt` alla versione `3.0.24`.
- Le dipendenze gestite automaticamente vengono ora installate sempre in `piboh-dip/`; i riferimenti a `piboh-temp/` sono stati rimossi.
- Il controllo integrita distingue ora tra elementi critici (rosso), opzionali (giallo) ed elementi presenti (verde).
- Il controllo integrita verifica anche la presenza della cartella `piboh-portable/PowerShell-7/` e di `pwsh.exe`.

## 3.0.23
- Aggiornato `piboh-script/version.txt` alla versione `3.0.23`.
- Gli script cercano ora prioritariamente `pwsh.exe` nel percorso `piboh-portable/PowerShell-7/` e, in fallback, nel resto di `piboh-portable/`.
- Riallineati `README.md` e `guide/GUIDA-SCRIPT-AUTOMATICO-WINDOWS.md` alla nuova versione centrale.

## 3.0.22
- Aggiornato `piboh-script/version.txt` alla versione `3.0.22`.
- Gli script cercano ora prioritariamente `pwsh.exe` dentro `piboh-portable/` e usano quella copia portable di PowerShell 7 se presente.
- Riallineati `README.md` e `guide/GUIDA-SCRIPT-AUTOMATICO-WINDOWS.md` alla nuova versione centrale.

## 3.0.19
- Aggiornato `piboh-script/version.txt` alla versione `3.0.19`.
- Completata la rimozione di **Git** dalla documentazione come dipendenza gestita dagli script automatici.
- Riallineati di nuovo `README.md` e `guide/GUIDA-SCRIPT-AUTOMATICO-WINDOWS.md` alla nuova versione centrale.

## 3.0.18
- Aggiornato `piboh-script/version.txt` alla versione `3.0.18`.
- Rimosso **Git** dalla gestione delle dipendenze automatiche degli script.
- Se il repository non è presente localmente e Git non è disponibile, l'installatore chiede di clonare manualmente XTetris o installare Git per conto proprio.
- Riallineati `README.md` e `guide/GUIDA-SCRIPT-AUTOMATICO-WINDOWS.md` alla nuova versione centrale.

## 3.0.16
- Aggiornato `piboh-script/version.txt` alla versione `3.0.16`.
- Corretto il disinstallatore: se una dipendenza è stata installata in modalità `piboh-temp`, ora viene rimossa direttamente dalla cartella temporanea senza provare l'uninstaller del pacchetto.
- Riallineati `README.md` e `guide/GUIDA-SCRIPT-AUTOMATICO-WINDOWS.md` alla nuova versione centrale.

## 3.0.13
- Aggiornato `piboh-script/version.txt` alla versione `3.0.13`.
- Il controllo integrità verifica ora anche `piboh-portable/Notepad++Portable/shortcuts.xml` e `piboh-portable/Notepad++Portable/plugins/NppMarkdownPanel/NppMarkdownPanel.dll`.
- Riallineati `README.md` e `guide/GUIDA-SCRIPT-AUTOMATICO-WINDOWS.md` alla nuova versione centrale.

## 3.0.12
- Aggiornato `piboh-script/version.txt` alla versione `3.0.12`.
- Rimossa la cartella del vecchio plugin `MarkdownViewerPlusPlus` dalla copia portable di Notepad++.
- Lasciato `NppMarkdownPanel` come plugin Markdown di riferimento, con `shortcuts.xml` configurato per `Ctrl+Shift+M`.
- Riallineati `README.md` e `guide/GUIDA-SCRIPT-AUTOMATICO-WINDOWS.md` alla nuova versione centrale.

## 3.0.11
- Aggiornato `piboh-script/version.txt` alla versione `3.0.11`.
- Integrato `NppMarkdownPanel` nella copia portable di Notepad++ al posto del riferimento principale a MarkdownViewer++.
- Aggiunto `shortcuts.xml` alla copia portable per associare `Ctrl+Shift+M` al comando di toggle del pannello Markdown.
- Aggiornati `README.md` e `guide/GUIDA-SCRIPT-AUTOMATICO-WINDOWS.md` alla nuova versione e al nuovo plugin Markdown.

## 3.0.10
- Aggiornato `piboh-script/version.txt` alla versione `3.0.10`.
- Corretto il file `piboh-script/installa-compila-windows.ps1` rimuovendo testo residuo non valido in coda.
- Riallineati `README.md` e `guide/GUIDA-SCRIPT-AUTOMATICO-WINDOWS.md` alla nuova versione centrale.

## 3.0.5
- Aggiornato `piboh-script/version.txt` alla versione `3.0.5`.
- Il controllo integrità verifica ora anche la presenza di `piboh-script/version.txt`.
- Aggiunta nel `README.md` una riga esplicita con la versione corrente degli script.

## 3.0.4
- Introdotto `piboh-script/version.txt` come fonte unica della versione degli script.
- Tutti i batch e gli script PowerShell leggono ora la versione da un file centrale.
- Aggiornati i riferimenti documentali per riflettere la versione unificata `3.0.4`.

## 3.0.3
- Aggiornate tutte le versioni dei file script e dei riferimenti documentali alla versione `3.0.3`.
- Installatore migliorato: scelta del percorso dipendenze, Git opzionale, uso di `--silent` e metadati delle installazioni.
- Disinstallatore migliorato: rimozione silenziosa dei pacchetti installati dallo script usando uninstaller nascosti o winget silenzioso.

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
