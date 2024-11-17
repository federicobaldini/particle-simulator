#ifndef PARTICLETYPE_H
#define PARTICLETYPE_H

#include <iostream>
#include <string>

// La classe ParticleType rappresenta una particella generica, definita
// da un nome, una massa e una carica. Fornisce metodi base per accedere
// e stampare le proprietà della particella.

class ParticleType
{
private:
  const std::string fName; // Nome della particella
  const double fMass;      // Massa della particella
  const int fCharge;       // Carica elettrica della particella

public:
  // Costruttore che inizializza le proprietà della particella.
  // name: nome della particella
  // mass: massa della particella
  // charge: carica elettrica della particella
  ParticleType(const std::string &name, double mass, int charge);

  // Metodi per accedere alle proprietà della particella:
  // return: nome della particella
  const std::string &GetName() const;

  // return: massa della particella
  double GetMass() const;

  // return: carica elettrica della particella
  int GetCharge() const;

  // Metodo virtuale per ottenere la larghezza della risonanza.
  // Di default restituisce 0 per particelle stabili.
  // return: larghezza della risonanza (default 0.0)
  virtual double GetWidth() const { return 0.0; }

  // Metodo virtuale per stampare le proprietà della particella.
  // Stampa nome, massa e carica.
  virtual void Print() const;
};

#endif // PARTICLETYPE_H