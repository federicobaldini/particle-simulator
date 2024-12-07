#ifndef PARTICLE_H
#define PARTICLE_H

#include "ParticleType.h"
#include <string>

// La classe Particle rappresenta una particella fisica, caratterizzata
// da un tipo, una quantità di moto e metodi per calcolare proprietà
// relativistiche e interagire con altre particelle.

class Particle
{
private:
  static ParticleType *fParticleType[];      // Array statico per memorizzare i tipi di particelle definiti
  static const int fMaxNumParticleType = 10; // Numero massimo di tipi di particelle che possono essere registrati
  static int fNParticleType;                 // Numero corrente di tipi di particelle registrati
  int fIndex;                                // Indice che identifica il tipo di particella
  double fPx, fPy, fPz;                      // Componenti della quantità di moto (Px, Py, Pz)

  // Metodo statico per trovare un tipo di particella dato il nome e restituendone l'indice
  // name: nome del tipo di particella
  // return: indice del tipo di particella o -1 se non trovato
  static int FindParticleType(const std::string &name);

  // Metodo per applicare un boost relativistico alla quantità di moto della particella
  // bx, by, bz: componenti della velocità relativistica
  void Boost(double bx, double by, double bz);

public:
  // Costruttore di default che inizializza una particella vuota
  Particle();

  // Costruttore parametrizzato che inizializza il tipo di particella e la quantità di moto
  // name: nome del tipo di particella
  // px, py, pz: componenti della quantità di moto (di default sono 0)
  Particle(const std::string &name, double px = 0, double py = 0, double pz = 0);

  // Metodo per accedere all'indice del tipo di particella
  int GetParticleTypeIndex() const;

  // Metodo statico per accedere ad un tipo di particella dato il suo indice
  // index: indice del tipo di particella
  // return: puntatore al tipo di particella o nullptr se l'indice non è valido
  static const ParticleType *GetParticleType(int index);

  // Metodi per accedere alle componenti della quantità di moto
  double GetPulseX() const { return fPx; } // Restituisce la componente Px
  double GetPulseY() const { return fPy; } // Restituisce la componente Py
  double GetPulseZ() const { return fPz; } // Restituisce la componente Pz

  // Metodo statico per aggiungere un nuovo tipo di particella al sistema
  // name: nome del tipo di particella
  // mass: massa della particella
  // charge: carica elettrica della particella
  // width: larghezza della risonanza (default 0 per particelle stabili)
  static void AddParticleType(const std::string &name, double mass, int charge, double width = 0);

  // Metodo per impostare il tipo di particella usando il nome
  // name: nome del tipo di particella
  void SetParticleTypeIndex(const std::string &name);

  // Metodo per impostare il tipo di particella usando l'indice
  // index: indice del tipo di particella
  void SetParticleTypeIndex(int index);

  // Metodo per stampare le proprietà della particella.
  // Stampa informazioni sul tipo di particella e sulla quantità di moto
  void Print() const;

  // Metodo per impostare le componenti della quantità di moto
  // px, py, pz: nuove componenti della quantità di moto
  void SetPulse(double px, double py, double pz);

  // Metodo per ottenere la massa della particella in base al suo tipo
  // return: massa della particella o 0 se l'indice non è valido
  double GetMass() const;

  // Metodo per ottenere l'energia totale della particella usando la relazione relativistica
  // return: energia totale della particella
  double GetEnergy() const;

  // Calcola la massa invariante con un'altra particella
  // other: altra particella
  // return: massa invariante
  double InvariantMass(const Particle &other) const;

  // Simula il decadimento della particella in due particelle figlie
  // dau1, dau2: particelle figlie risultanti dal decadimento
  // return: stato del decadimento (0: successo, 1: errore di massa zero, 2: massa insufficiente)
  int Decay2Body(Particle &dau1, Particle &dau2) const;
};

#endif // PARTICLE_H