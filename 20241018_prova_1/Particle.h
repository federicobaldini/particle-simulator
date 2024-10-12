#ifndef PARTICLE_H // Inizio dell'include guard per prevenire l'inclusione multipla del file.
#define PARTICLE_H // Definiamo PARTICLE_H per garantire che il file non venga incluso più volte nello stesso progetto.

#include "ParticleType.h" // Include il file header "ParticleType.h", che contiene la definizione della classe `ParticleType`.
// Questo include è necessario perché `Particle` utilizza la classe `ParticleType`.

#include <vector> // Include la libreria standard C++ per i vettori (`std::vector`), che viene utilizzata per memorizzare i tipi di particelle.

// Definizione della classe `Particle`, che gestisce una singola particella.
// La classe `Particle` contiene informazioni sul tipo di particella, l'impulso e metodi per gestire queste proprietà.
class Particle
{
public:
  // Costruttore parametrico della classe `Particle`.
  // Prende come parametri le tre componenti dell'impulso (`px`, `py`, `pz`) e un indice (`index`) che identifica il tipo di particella.
  // Quando crei un oggetto `Particle`, questo costruttore inizializza l'impulso e il tipo di particella con i valori forniti.
  Particle(double px, double py, double pz, int index);

  // Questo metodo restituisce l'indice della particella.
  // L'indice è un numero intero che rappresenta la posizione di questo tipo di particella nell'array statico `fParticleTypes`.
  int GetIndex() const;

  // Questo metodo imposta l'indice della particella (ossia, il tipo di particella).
  // Viene usato per cambiare l'identità della particella associata all'oggetto `Particle`.
  void SetIndex(int index);

  // Questo metodo imposta le componenti dell'impulso della particella.
  // L'impulso è un vettore 3D con componenti lungo gli assi x, y e z.
  void SetP(double px, double py, double pz);

  // Questo è un metodo statico che permette di aggiungere un nuovo tipo di particella all'array statico `fParticleTypes`.
  // Poiché è un metodo statico, può essere chiamato senza bisogno di creare un oggetto `Particle`.
  static void AddParticleType(const ParticleType *type);

  // Questo metodo statico stampa tutti i tipi di particelle presenti nell'array `fParticleTypes`.
  // Anche questo è statico, quindi può essere chiamato senza istanziare un oggetto `Particle`.
  static void PrintArray();

  // Questo è un metodo statico che cerca una particella nell'array `fParticleTypes` in base al suo nome.
  // Restituisce l'indice della particella trovata oppure un valore che indica che la particella non è stata trovata.
  static int FindParticle(const std::string &name);

  // Metodo per calcolare l'energia totale della particella (secondo la formula relativistica)
  double CalculateEnergy() const;

private:
  // Questi tre membri rappresentano le componenti dell'impulso della particella lungo gli assi x, y e z.
  // Ogni particella ha un impulso che può variare da evento a evento.
  double fPx, fPy, fPz;

  // Questo è un intero che rappresenta l'indice della particella, ossia il tipo di particella.
  // L'indice è usato per accedere al tipo di particella corretto nell'array `fParticleTypes`.
  int fIndex;

  // Questo è un array statico che contiene i tipi di particelle.
  // Il vettore è statico, quindi è condiviso tra tutte le istanze di `Particle` (esiste una sola copia per tutte le particelle).
  // Ogni elemento dell'array è un puntatore a un oggetto di tipo `ParticleType`.
  static std::vector<const ParticleType *> fParticleTypes;
};

#endif // PARTICLE_H  // Fine dell'include guard per prevenire inclusioni multiple.