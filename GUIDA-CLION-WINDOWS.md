# GUIDA CLION SU WINDOWS - XTetris

Questa guida spiega come aprire, configurare, compilare ed eseguire XTetris con **CLion** su Windows.

## 1. Requisiti

Installa:

- **CLion**
- **CMake**
- **MSYS2 MinGW-w64** oppure un toolchain GCC compatibile

> Per questo progetto è preferibile usare una toolchain **GCC/MinGW**.

---

## 2. Apri il progetto

1. Avvia CLion
2. Seleziona **Open**
3. Apri la cartella del repository `XTetris`

CLion rileverà automaticamente il file `CMakeLists.txt`.

---

## 3. Configura la toolchain

Vai in:

- **File > Settings > Build, Execution, Deployment > Toolchains**

Imposta una toolchain con:

- **C Compiler** → GCC
- **C++ Compiler** → G++
- **Debugger** → GDB (opzionale)
- **CMake** → quello installato sul sistema

Se usi MSYS2, i percorsi tipici sono simili a:

```text
C:\msys64\ucrt64\bin\gcc.exe
C:\msys64\ucrt64\bin\g++.exe
C:\msys64\ucrt64\bin\gdb.exe
```

---

## 4. Configura CMake profile

Vai in:

- **File > Settings > Build, Execution, Deployment > CMake**

Verifica che il profilo punti alla toolchain corretta.

Puoi usare il generatore di default oppure Ninja, se disponibile.

---

## 5. Build del progetto

Una volta configurata la toolchain:

- premi **Build Project**
- oppure usa il pulsante Run/Build in alto

CLion compilerà `main.c` e gli altri file del progetto tramite CMake.

---

## 6. Avvia il gioco

Configura una **Run Configuration** per l'eseguibile `XTetris`.

Poi avvialo con **Run**.

> Importante: XTetris è un programma interattivo da console. Assicurati che venga eseguito in una console dove puoi scrivere input.

---

## 7. Come usare il gioco

Il gioco chiede input testuali e numerici da tastiera:

- modalità (`1`, `2`, `3`, `4`)
- tricky mode (`1` o `0`)
- nome giocatore
- tetramino
- rotazione
- colonna

---

## 8. Problemi comuni in CLion

### Il compilatore non viene trovato

Controlla la configurazione della toolchain.

### Il programma parte ma non riceve input bene

Prova a eseguirlo in una console esterna o in un terminale integrato configurato correttamente.

### I colori o l'allineamento sono strani

È normale in alcune console Windows. Meglio usare **Windows Terminal** o terminali compatibili ANSI.

---

## 9. Metodo alternativo

Se vuoi evitare la configurazione manuale iniziale, usa prima lo script:

```powershell
powershell -ExecutionPolicy Bypass -File .\scripts\installa-compila-windows.ps1
```

Poi apri il progetto in CLion con i prerequisiti già installati.
