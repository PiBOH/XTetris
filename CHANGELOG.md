# CHANGELOG

## 3.1.13
- Aggiornato `piboh-script/version.txt` alla versione `3.1.13`.
- Riallineati definitivamente `README.md`, `guide/GUIDA-SCRIPT-AUTOMATICO-WINDOWS.md` e `CHANGELOG.md` alla stessa versione centrale.
- Confermato lo stato finale del supporto a `piboh-temp/`, `PowerShell-7` portable e `NppMarkdownPanel`.

## 3.1.7
- Aggiornato `piboh-script/version.txt` alla versione `3.1.7`.
- Riallineati definitivamente `README.md`, `guide/GUIDA-SCRIPT-AUTOMATICO-WINDOWS.md` e `CHANGELOG.md` alla stessa versione centrale.
- Confermato lo stato attuale del supporto a `piboh-temp/`, `PowerShell-7` portable e `NppMarkdownPanel`.

## 3.1.3
- Aggiornato `piboh-script/version.txt` alla versione `3.1.3`.
- Notepad++ Portable usa ora `plugins/Config/NppMarkdownPanel.ini` per aprire automaticamente il pannello di preview Markdown sui file supportati.
- Rimosso il tentativo di attivazione via `SendKeys` dal launcher delle guide.
- La disinstallazione pulisce ora anche `piboh-temp/`, `installed-packages.txt` e `installed-packages.csv`.

## 3.1.2
- Aggiornato `piboh-script/version.txt` alla versione `3.1.2`.
- Gli script cercano ora `pwsh.exe` sia in `piboh-portable/PowerShell-7/` sia in `piboh-portable/PowerShell-7.7.0-preview.2-win-x64/` prima di usare il fallback.
- Aggiornata la documentazione per riflettere la struttura reale trovata sul repository GitHub.

## 3.1.1
- Allineata la numerazione degli script alla nuova serie `3.1.x` richiesta.
- Confermato il ripristino del flusso stabile con `piboh-temp/`.
- Confermata la presenza della funzione `Resolve-InstalledPackageLocation` nello script di installazione e il relativo fix per l'errore che bloccava il processo.

## 3.0.45
- Aggiornato `piboh-script/version.txt` alla versione `3.0.45`.
- Riallineati `README.md` e `guide/GUIDA-SCRIPT-AUTOMATICO-WINDOWS.md` alla versione centrale corrente.
- Consolidato il versionamento dopo l'eccezione `3.0.44.1` e ripristinato l'incremento normale.

## 3.0.44.1
- Aggiornato `piboh-script/version.txt` alla versione `3.0.44.1`.
- Riallineati `README.md` e `guide/GUIDA-SCRIPT-AUTOMATICO-WINDOWS.md` a questa versione intermedia speciale.
- Nessuna modifica funzionale aggiuntiva: aggiornamento eccezionale della versione su richiesta.

## 3.0.44
- Riallineati definitivamente `README.md` e `guide/GUIDA-SCRIPT-AUTOMATICO-WINDOWS.md` alla versione centrale dopo il ripristino stabile di `piboh-temp/` e della funzione `Resolve-InstalledPackageLocation`.
- Consolidata la documentazione finale del comportamento attuale dell'installer/disinstallatore.

## 3.0.42
- Corretto l'ultimo riferimento residuo a `3.0.39` dentro `guide/GUIDA-SCRIPT-AUTOMATICO-WINDOWS.md`.
- Riallineati di nuovo `README.md` e guida script alla versione centrale.

## 3.0.41
- Riallineati definitivamente `README.md` e `guide/GUIDA-SCRIPT-AUTOMATICO-WINDOWS.md` alla versione centrale dopo la correzione del riferimento rimasto a `3.0.39`.
- Confermata la presenza della funzione `Resolve-InstalledPackageLocation` nello script di installazione.

## 3.0.40
- Ripristinata la funzione `Resolve-InstalledPackageLocation` nello script di installazione, correggendo l'errore che impediva di completare l'installazione dopo la reinstallazione di MSYS2/CMake.
- Riallineati `README.md` e `guide/GUIDA-SCRIPT-AUTOMATICO-WINDOWS.md` alla nuova versione centrale.

## 3.0.39
- Confermato il ripristino stabile di `piboh-temp/` come cartella per le dipendenze gestite automaticamente.

## 3.0.38
- Ripristinata e consolidata l'installazione delle dipendenze in `piboh-temp/`.
- Confermata la correzione dell'installer per MSYS2/CMake con ricerca più robusta e controllo di usabilità meno fragile.

## 3.0.33
- Confermata la correzione dell'installatore per MSYS2: se il pacchetto risulta installato ma non è utilizzabile nel percorso atteso, viene tentata una reinstallazione/repair con `--force`.

## 3.0.31
- Corretto `Find-Msys2Root` nell'installatore: ora cerca MSYS2 sia in `piboh-dip/` sia in `piboh-dip/MSYS2/`, e usa anche i metadati salvati dall'installazione.

## 3.0.29
- Confermato l'uso prioritario di `piboh-portable/PowerShell-7/pwsh.exe` quando presente.

## 3.0.28
- Corretto definitivamente il blocco delle versioni nella guida script, riallineandolo alla versione centrale.

## 3.0.27
- Confermata la struttura `piboh-portable/PowerShell-7/` come percorso portable preferito per `pwsh.exe`.

## 3.0.24
- Il controllo integrita distingue tra elementi critici (rosso), opzionali (giallo) ed elementi presenti (verde).
- Il controllo integrita verifica anche la presenza della cartella `piboh-portable/PowerShell-7/` e di `pwsh.exe`.

## 3.0.23
- Gli script cercano prioritariamente `pwsh.exe` nel percorso `piboh-portable/PowerShell-7/` e, in fallback, nel resto di `piboh-portable/`.

## 3.0.11
- Integrato `NppMarkdownPanel` nella copia portable di Notepad++ al posto del riferimento principale a MarkdownViewer++.
- Aggiunto `shortcuts.xml` alla copia portable per associare `Ctrl+Shift+M` al comando di toggle del pannello Markdown.

## Modifiche funzionali precedenti
- Creati script Windows per installazione e compilazione automatica.
- Spostate le guide nella cartella `guide/`.
- Spostati gli script nella cartella `piboh-script/`.
- Integrata copia **Notepad++ Portable** in `piboh-portable/Notepad++Portable/`.
- Creato `AVVIA GIOCO.bat` generato automaticamente dopo una build riuscita.
- Aggiunti log e tracciamento dei pacchetti installati dagli script.
- Aggiunta disinstallazione controllata di dipendenze e artefatti compilati.

> [!NOTE]
>
> File genereted whit [Arena AI](https://arena.ai).
