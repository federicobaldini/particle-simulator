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
  // Array statico per memorizzare i tipi di particelle definiti
  static ParticleType *fParticleType[];

  // Numero massimo di tipi di particelle che possono essere registrati
  static const int fMaxNumParticleType = 10;

  // Numero corrente di tipi di particelle registrati
  static int fNParticleType;

  // Indice che identifica il tipo di particella
  int fIndex;

  // Componenti della quantità di moto (Px, Py, Pz)
  double fPx, fPy, fPz;

  // Trova il tipo di particella dato il nome, restituendo il suo indice
  static int FindParticleType(const std::string &name);

  // Applica un boost relativistico alla quantità di moto della particella
  void Boost(double bx, double by, double bz);

public:
  // Costruttore di default che inizializza una particella vuota
  Particle();

  // Costruttore parametrizzato che inizializza il tipo di particella e la quantità di moto
  // name: nome del tipo di particella
  // px, py, pz: componenti della quantità di moto (di default sono 0)
  Particle(const std::string &name, double px = 0, double py = 0, double pz = 0);

  // Metodo per ottenere l'indice del tipo di particella
  int GetParticleTypeIndex() const;

  // Metodo statico per ottenere un tipo di particella dato il suo indice
  static const ParticleType *GetParticleType(int index);

  // Getter per le componenti della quantità di moto
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
  void SetParticleTypeIndex(const std::string &name);

  // Metodo per impostare il tipo di particella usando l'indice
  void SetParticleTypeIndex(int index);

  // Stampa informazioni sul tipo di particella e sulla quantità di moto
  void Print() const;

  // Imposta le componenti della quantità di moto
  // px, py, pz: nuove componenti della quantità di moto
  void SetPulse(double px, double py, double pz);

  // Restituisce la massa della particella in base al suo tipo
  double GetMass() const;

  // Calcola l'energia totale della particella usando la relazione relativistica
  double GetEnergy() const;

  // Calcola la massa invariante con un'altra particella
  // other: altra particella per il calcolo
  double InvariantMass(const Particle &other) const;

  // Simula il decadimento della particella in due particelle figlie
  // dau1, dau2: particelle figlie risultanti dal decadimento
  // return: stato del decadimento (successo o fallimento)
  int Decay2Body(Particle &dau1, Particle &dau2) const;
};

#endif // PARTICLE_H