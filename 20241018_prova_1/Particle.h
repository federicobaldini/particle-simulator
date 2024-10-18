#ifndef PARTICLE_H
#define PARTICLE_H

#include "ParticleType.h"
#include <string>

class Particle
{
private:
  // Array statico di puntatori a ParticleType, rappresenta i tipi di particelle disponibili
  static ParticleType *fParticleType[];

  // Numero massimo di tipi di particelle che possono essere gestiti
  static const int fMaxNumParticleType = 10;

  // Contatore statico per il numero di tipi di particelle già inseriti
  static int fNParticleType;

  // Indice del tipo di particella nell'array fParticleType
  int fIndex;

  // Componenti dell'impulso della particella
  double fPx, fPy, fPz;

  // Metodo privato per cercare un tipo di particella nell'array fParticleType
  static int FindParticle(const std::string &name);

public:
  // Costruttore parametrico con valori di default per l'impulso
  Particle(const std::string &name, double px = 0, double py = 0, double pz = 0);

  // Getter per l'indice del tipo di particella
  int GetIndex() const;

  // Getter per le componenti dell'impulso, dichiarati const per non modificare l'oggetto
  double GetPx() const { return fPx; }
  double GetPy() const { return fPy; }
  double GetPz() const { return fPz; }

  // Metodo statico per aggiungere un nuovo tipo di particella all'array fParticleType
  static void AddParticleType(const std::string &name, double mass, int charge, double width = 0);

  // Metodo che imposta l'indice della particella cercandola per nome o per indice
  void SetIndex(const std::string &name);
  void SetIndex(int index);

  // Metodo che stampa le proprietà della particella
  void Print() const;

  // Metodo per settare le componenti dell'impulso
  void SetP(double px, double py, double pz);

  // Metodo che restituisce la massa della particella
  double GetMass() const;

  // Metodo che calcola l'energia totale della particella
  double GetEnergy() const;

  // Metodo che calcola la massa invariante tra questa particella e un'altra
  double InvMass(const Particle &other) const;
};

#endif // PARTICLE_H