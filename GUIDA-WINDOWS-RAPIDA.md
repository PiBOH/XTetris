# GUIDA WINDOWS RAPIDA - XTetris

Questa è la versione più corta possibile per compilare ed eseguire **XTetris originale da terminale su Windows**.

## Requisiti

Installa:

- **Git**
- **CMake**
- **MSYS2 / MinGW-w64**

Se preferisci automatizzare tutto, usa lo script:

- `scripts/installa-compila-windows.ps1`
- oppure `scripts/installa-compila-windows.bat`

---

## Metodo rapido manuale

### 1. Clona il repository

```powershell
git clone https://github.com/PiBOH/XTetris.git
cd XTetris
```

### 2. Crea la build

```powershell
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
cmake --build .
```

### 3. Avvia il gioco

```powershell
.\XTetris.exe
```

---

## Uso del gioco

Menu iniziale:

- `1` = SinglePlayer
- `2` = Multiplayer vs persona
- `3` = Multiplayer vs PC
- `4` = Esci

Poi il gioco ti chiederà, di volta in volta:

- se vuoi la tricky mode (`1` sì / `0` no)
- nome giocatore
- ID tetramino
- ID rotazione
- colonna (`0`-`9`)

---

## Se qualcosa non funziona

### `gcc` non trovato

Installa o configura **MinGW-w64**.

### `cmake` non trovato

Installa **CMake**.

### Il gioco si chiude subito

Non usare doppio click: avvialo sempre da **PowerShell** o **Windows Terminal**.

---

## Alternativa consigliata

Per fare tutto automaticamente su Windows:

```powershell
powershell -ExecutionPolicy Bypass -File .\scripts\installa-compila-windows.ps1
```
***
> [!NOTE]
> File genereted whit [Arena AI](https://arena.ai/)
<!-- File Generato con Arena AI (https://arena.ai/) -->
