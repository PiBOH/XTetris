# GUIDA VS CODE + CMAKE TOOLS SU WINDOWS - XTetris

Questa guida spiega come usare XTetris con **Visual Studio Code** su Windows.

## 1. Requisiti

Installa:

- **Visual Studio Code**
- estensione **C/C++**
- estensione **CMake Tools**
- **CMake**
- **MSYS2 / MinGW-w64 GCC**

---

## 2. Apri il progetto

1. Apri VS Code
2. Seleziona **Open Folder**
3. Apri la cartella del repository `XTetris`

---

## 3. Installa le estensioni

Nel marketplace di VS Code installa:

- **C/C++** (Microsoft)
- **CMake Tools** (Microsoft)

---

## 4. Configura la toolchain

Assicurati che GCC e CMake siano accessibili nel `PATH`, oppure configura i percorsi corretti.

Con MSYS2 UCRT64, i binari si trovano tipicamente in:

```text
C:\msys64\ucrt64\bin
```

---

## 5. Configura CMake

Apri il Command Palette e usa:

- `CMake: Select a Kit`

Seleziona un kit GCC/MinGW adatto.

Poi esegui:

- `CMake: Configure`
- `CMake: Build`

---

## 6. Esegui il gioco

Una volta completata la build, esegui il binario generato.

Di solito si troverà nella cartella `build`:

```powershell
.\build\XTetris.exe
```

Puoi farlo da terminale integrato di VS Code.

---

## 7. Interazione col gioco

XTetris funziona come programma da console. Devi inserire:

- modalità di gioco
- risposte sì/no come `1` o `0`
- nomi giocatore
- ID di tetramini e rotazioni
- colonne

---

## 8. Problemi comuni

### VS Code non trova CMake

Verifica che CMake sia installato e nel `PATH`.

### VS Code non trova GCC

Verifica che la toolchain MinGW/MSYS2 sia nel `PATH` o selezionata nel kit.

### Il programma si comporta male in console

Prova il terminale integrato oppure esegui `XTetris.exe` in **Windows Terminal**.

---

## 9. Scorciatoia consigliata

Per evitare configurazioni manuali iniziali, lancia prima lo script automatico del repo:

```powershell
powershell -ExecutionPolicy Bypass -File .\scripts\installa-compila-windows.ps1
```

Questo installerà i prerequisiti principali e compilerà il progetto.
