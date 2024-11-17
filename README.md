# Particle Simulation and Analysis

Questo progetto simula eventi di collisione tra particelle, genera casualmente le loro proprietà (come angoli, quantità di moto e tipi) e calcola proprietà derivate come energia e massa invariante. Utilizza il framework **ROOT** per la visualizzazione e l'analisi statistica dei risultati mediante istogrammi.

## Indice

- [Introduzione](#introduzione)
- [Struttura del Progetto](#struttura-del-progetto)
- [Prerequisiti](#prerequisiti)
- [Compilazione e Esecuzione](#compilazione-e-esecuzione)
- [Descrizione dei File Principali](#descrizione-dei-file-principali)
  - [main.cpp](#maincpp)
  - [Classi](#classi)
  - [Macro ROOT](#macro-root)
- [Analisi dei Risultati](#analisi-dei-risultati)
- [Directory e File di Output](#directory-e-file-di-output)
- [Note Aggiuntive](#note-aggiuntive)
- [Autore](#autore)

## Introduzione

Il progetto simula eventi di collisione generando casualmente particelle con specifiche proprietà fisiche. Include il decadimento di particelle risonanti (come il \( K^\* \)), con conservazione della quantità di moto e generazione di prodotti di decadimento. Gli istogrammi risultanti vengono analizzati per verificare la coerenza con le distribuzioni teoriche attese.

## Struttura del Progetto

- `src/`: Contiene il codice sorgente C++ e le macro ROOT.
  - `main.cpp`: Programma principale per la simulazione.
  - `ParticleType.h` / `ParticleType.cpp`: Definisce la classe base per i tipi di particelle.
  - `ResonanceType.h` / `ResonanceType.cpp`: Estende `ParticleType` per le risonanze.
  - `Particle.h` / `Particle.cpp`: Classe che rappresenta una particella.
  - `utils/`: Contiene le macro ROOT per l'analisi.
- `root/data/`: Directory per i file ROOT generati.
- `charts/`: Directory per i grafici generati dalle macro ROOT.

## Prerequisiti

- **ROOT**: Framework per il calcolo scientifico e l'analisi dei dati. Assicurarsi che sia installato e configurato correttamente.
- **Compilatore C++**: GCC o Clang con supporto per C++11 o superiore.

## Compilazione e Esecuzione

### Compilazione

Per compilare il programma principale:

```bash
g++ -std=c++11 -o particle_sim ParticleType.cpp ResonanceType.cpp Particle.cpp main.cpp $(root-config --cflags --libs)
```

### Esecuzione

Per eseguire il programma:

```bash
./particle_sim
```

Il programma genererà il file `ParticleAnalysis.root` nella directory `root/data/`, contenente tutti gli istogrammi prodotti durante la simulazione.

## Descrizione dei File Principali

### main.cpp

Il file `main.cpp` è il cuore della simulazione. Esegue i seguenti passi:

1. **Inizializzazione**: Definisce i tipi di particelle supportati e imposta il generatore di numeri casuali.
2. **Generazione degli Eventi**: Simula 100.000 eventi di collisione, ciascuno contenente 100 particelle iniziali.
3. **Assegnazione delle Proprietà**:
   - Genera casualmente gli angoli azimutali (\( \phi \)) e polari (\( \theta \)).
   - Calcola la quantità di moto (\( p \)) con una distribuzione esponenziale media di 1 GeV.
   - Converte le coordinate sferiche in cartesiane per ottenere \( p_x \), \( p_y \), \( p_z \).
4. **Determinazione del Tipo di Particella**: Assegna il tipo di particella in base a probabilità prefissate:
   - Pion+ e Pion-: 40% ciascuno.
   - Kaon+ e Kaon-: 5% ciascuno.
   - Proton+ e Proton-: 4.5% ciascuno.
   - K\*: 1%.
5. **Gestione delle Risonanze**:
   - Decadimento del \( K^\* \) in un pione e un kaone.
6. **Riempimento degli Istogrammi**: Registra le proprietà delle particelle.
7. **Calcolo delle Masse Invarianti**.
8. **Salvataggio dei Dati**: Gli istogrammi vengono salvati in `ParticleAnalysis.root`.

### Classi

- **ParticleType**: Rappresenta un tipo di particella (nome, massa, carica).
- **ResonanceType**: Estende `ParticleType` per includere la larghezza di decadimento.
- **Particle**: Rappresenta una particella con quantità di moto ed energia. Supporta il calcolo della massa invariante e il decadimento.

### Macro ROOT

- **verify_particle_distribution.cpp**: Verifica la coerenza delle proporzioni delle particelle generate.
- **check_momentum_distribution.cpp**: Controlla la distribuzione esponenziale dell'impulso.
- **check_angular_distributions.cpp**: Verifica la distribuzione uniforme degli angoli.
- **analyze_invariant_mass.cpp**: Analizza gli istogrammi di massa invariante e esegue fit gaussiani.
- **analyze_histograms.cpp**: Salva tutti gli istogrammi come file PDF.

## Analisi dei Risultati

Dopo la simulazione, usa le macro per analizzare i risultati:

- **Distribuzioni di Proprietà delle Particelle**.
- **Distribuzione dell'Impulso**: Verifica l'andamento esponenziale.
- **Distribuzioni Angolari**.
- **Masse Invarianti**: Identificazione dei picchi dovuti a risonanze.

## Directory e File di Output

- **root/data/ParticleAnalysis.root**: File con gli istogrammi generati.
- **charts/**: Contiene i grafici (PDF).

## Note Aggiuntive

- **Compilazione delle Macro**: Usa:

```bash
root -l -b -q root/utils/nome_macro.cpp
```

- **Configurazione**: Verifica i percorsi per ROOT e file di output.
- **Dipendenze**: Assicurati di avere ROOT configurato correttamente.

## Autore

- **Nome**: Federico Baldini
- **Email**: [federico.baldini7@studio.unibo.it](mailto:federico.baldini7@studio.unibo.it)
