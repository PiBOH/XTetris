# GUIDA MSYS2 - XTetris su Windows

Questa guida spiega come compilare XTetris usando **MSYS2**, che è il metodo più consigliato su Windows per questo progetto.

## Perché MSYS2

XTetris è un progetto C da terminale. MSYS2 fornisce:

- GCC
- make / ninja
- CMake
- ambiente compatibile con toolchain GNU

È quindi una scelta molto adatta per questo repository.

---

## 1. Installa MSYS2

Scaricalo da:

- https://www.msys2.org/

Dopo l'installazione, apri il terminale:

- **MSYS2 UCRT64**

> Consiglio: usa **UCRT64**, non il terminale MSYS generico.

---

## 2. Aggiorna i pacchetti

Nel terminale MSYS2 UCRT64:

```bash
pacman -Syu
```

Se il terminale ti chiede di chiudere e riaprire, fallo.
Poi esegui di nuovo:

```bash
pacman -Su
```

---

## 3. Installa i pacchetti necessari

```bash
pacman -S --needed mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-ninja git
```

---

## 4. Clona il repository

```bash
git clone https://github.com/PiBOH/XTetris.git
cd XTetris
```

---

## 5. Compila con CMake + Ninja

```bash
cmake -S . -B build -G Ninja
cmake --build build
```

---

## 6. Avvia il gioco

```bash
./build/XTetris.exe
```

---

## 7. Flusso di utilizzo

Quando il gioco parte:

- scegli la modalità (`1`, `2`, `3`, `4`)
- scegli se attivare la tricky mode (`1` o `0`)
- inserisci i nomi richiesti
- seleziona tetramino, rotazione e colonna

---

## 8. Note utili

### Colori ANSI

Su Windows Terminal e MSYS2 i colori in genere funzionano meglio rispetto al Prompt dei comandi classico.

### Layout terminale

Usa un font monospaziato e una finestra abbastanza larga, perché il gioco stampa la griglia in testo.

---

## 9. Comando unico di build

Se sei già dentro il repo:

```bash
cmake -S . -B build -G Ninja && cmake --build build
```

---

## 10. Alternativa automatica

Se vuoi evitare questi passaggi manuali, puoi usare lo script PowerShell fornito nel repo:

```powershell
powershell -ExecutionPolicy Bypass -File .\piboh-script\installa-compila-windows.ps1
```

## Guide collegate

- [Guida completa Windows](GUIDA-WINDOWS.md)
- [Guida rapida Windows](GUIDA-WINDOWS-RAPIDA.md)
- **Guida MSYS2** (guida corrente)
- [Guida CLion su Windows](GUIDA-CLION-WINDOWS.md)
- [Guida VS Code su Windows](GUIDA-VSCODE-WINDOWS.md)
- [Guida script automatico Windows](GUIDA-SCRIPT-AUTOMATICO-WINDOWS.md)

> [!NOTE]
>
> File genereted whit [Arena AI](https://arena.ai).
