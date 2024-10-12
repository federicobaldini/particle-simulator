#include "Particle.h" // Includiamo il file "Particle.h" che contiene la dichiarazione della classe `Particle`.
// Questo include è necessario per implementare le funzioni della classe definite in "Particle.h".

#include <iostream> // Includiamo la libreria standard per l'input/output in C++, necessaria per usare `std::cout` per la stampa.
#include <cmath>    // Includiamo la libreria standard C++ per le funzioni matematiche, come `sqrt()` o `pow()`, utili per i calcoli.

// Inizializzazione dell'array statico `fParticleTypes`, che memorizza i tipi di particelle.
// Poiché l'array è statico, viene inizializzato una sola volta e condiviso tra tutte le istanze della classe `Particle`.
std::vector<const ParticleType *> Particle::fParticleTypes;

// Costruttore della classe `Particle`.
// Il costruttore prende le tre componenti dell'impulso (`px`, `py`, `pz`) e un indice (`index`) che identifica il tipo di particella.
// Questi valori vengono usati per inizializzare i membri della classe `fPx`, `fPy`, `fPz`, e `fIndex`.
Particle::Particle(double px, double py, double pz, int index)
    : fPx(px), fPy(py), fPz(pz), fIndex(index) {} // La lista di inizializzazione assegna direttamente i valori alle variabili membro.

// Metodo per ottenere l'indice della particella.
// Restituisce il valore di `fIndex`, che rappresenta il tipo di particella, come "Proton", "Pion", ecc.
// Questo valore corrisponde alla posizione della particella nell'array `fParticleTypes`.
int Particle::GetIndex() const
{
  return fIndex;
}

// Metodo per impostare l'indice della particella.
// Questo permette di cambiare il tipo di particella associato a un oggetto `Particle`.
// L'indice viene passato come argomento e memorizzato in `fIndex`.
void Particle::SetIndex(int index)
{
  fIndex = index;
}

// Metodo per impostare l'impulso della particella.
// Le tre componenti dell'impulso (px, py, pz) vengono passate come argomenti e assegnate alle variabili membro `fPx`, `fPy`, e `fPz`.
// Questo metodo è usato per aggiornare l'impulso di una particella.
void Particle::SetP(double px, double py, double pz)
{
  fPx = px;
  fPy = py;
  fPz = pz;
}

// Metodo statico per aggiungere nuovi tipi di particelle.
// `type` è un puntatore a un oggetto `ParticleType` che viene aggiunto all'array statico `fParticleTypes`.
// Questo metodo consente di inserire nuovi tipi di particelle nel sistema.
void Particle::AddParticleType(const ParticleType *type)
{
  fParticleTypes.push_back(type); // Aggiunge il puntatore all'array `fParticleTypes`.
}

// Metodo statico per stampare tutti i tipi di particelle.
// Scorre l'array statico `fParticleTypes` e chiama il metodo `Print()` su ogni elemento.
// Questo permette di visualizzare le informazioni di tutte le particelle memorizzate nel sistema.
void Particle::PrintArray()
{
  // Utilizza un ciclo "range-based for loop" per iterare su ogni tipo di particella nell'array `fParticleTypes`.
  for (const auto &type : fParticleTypes) // `const auto&` permette di iterare in modo efficiente senza copiare gli oggetti.
  {
    type->Print(); // Chiama il metodo `Print()` per ogni tipo di particella, che stampa le sue informazioni.
  }
}

// Metodo privato per trovare una particella in base al nome.
// Scorre l'array `fParticleTypes` e confronta il nome di ciascun tipo di particella con il nome passato come argomento.
// Restituisce l'indice della particella se viene trovata, oppure -1 se la particella non esiste nell'array.
int Particle::FindParticle(const std::string &name)
{
  // Cicla su ogni elemento dell'array `fParticleTypes` per cercare il tipo di particella con il nome corrispondente.
  for (size_t i = 0; i < fParticleTypes.size(); ++i) // `size_t` è un tipo di dato usato per contatori non negativi.
  {
    if (fParticleTypes[i]->GetName() == name) // Confronta il nome della particella corrente con il nome passato come argomento.
    {
      return i; // Se il nome corrisponde, restituisce l'indice della particella.
    }
  }
  return -1; // Se nessuna particella con quel nome viene trovata, restituisce -1.
}

// Metodo per calcolare l'energia totale di una particella (secondo la formula relativistica).
// La formula utilizzata è E^2 = p^2 + m^2, dove E è l'energia totale, p è la quantità di moto, e m è la massa.
// La quantità di moto è data da p^2 = px^2 + py^2 + pz^2, e m è la massa della particella.
double Particle::CalculateEnergy() const
{
  // Otteniamo l'indice della particella, che ci permette di accedere al tipo di particella corretto.
  int index = GetIndex();

  // Otteniamo la massa della particella utilizzando l'indice per accedere all'array `fParticleTypes`.
  double mass = fParticleTypes[index]->GetMass(); // Chiama il metodo `GetMass()` della particella.

  // Calcoliamo la quantità di moto della particella (p^2 = px^2 + py^2 + pz^2).
  double momentum = sqrt(fPx * fPx + fPy * fPy + fPz * fPz); // Formula per la quantità di moto.

  // Calcoliamo l'energia totale utilizzando la formula relativistica: E^2 = p^2 + m^2.
  return sqrt(momentum * momentum + mass * mass); // Restituisce l'energia totale.
}