# pythia-root-analysis

Generacja zdarzeń w Pythii 8, analiza i wykresy w ROOT-cie.

## Wymagania

- CMake ≥ 3.20, kompilator z obsługą C++17
- ROOT
- Pythia 8.318, zbudowana lokalnie

## Instalacja

Pythia musi znajdować się w katalogu `pythia8318` obok repozytorium (katalog nadrzędny może mieć dowolną nazwę):

```
<katalog_nadrzędny>/
├── pythia8318/
└── pythia-root-analysis/
```

```bash
cd pythia8318
./configure && make -j
cd ../pythia-root-analysis
chmod +x run
```

Jeśli ROOT nie jest zainstalowany systemowo, należy wcześniej załadować jego środowisko:

```bash
source /ścieżka/do/root/bin/thisroot.sh
```

Inną lokalizację Pythii ustawia się w `CMakeLists.txt` (`set(PYTHIA8 ../pythia8318)`).

## Użycie

Komendy uruchamia się z katalogu głównego repozytorium.

| Komenda      | Działanie                                                        |
|--------------|------------------------------------------------------------------|
| `./run gen`  | Budowa projektu i generacja zdarzeń. Zapisze zdarzenia do `events.root` |
| `./run ana`  | Analiza (`macros/analysis.C`). Stworzy plik `analysis.root`          |
| `./run plot` | Wykresy (`macros/draw_plots.C`). Zapisze wykresy do `plots.pdf`                      |
| `./run all`  | Wszystkie kroki po kolei (to samo co `./run`)                    |

Parametry generacji zmienia się w `include/main.cmnd`.
