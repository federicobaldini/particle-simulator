#ifndef PARTICLE_H
#define PARTICLE_H

#include "ParticleType.h"
#include <vector>

class Particle
{
public:
  // Costruttore parametrico per impostare l'impulso e il tipo di particella
  Particle(double px, double py, double pz, int index);

  // Metodi per ottenere e impostare l'indice
  int GetIndex() const;
  void SetIndex(int index);

  // Metodi per impostare l'impulso
  void SetP(double px, double py, double pz);

  // Metodo statico per aggiungere nuovi tipi di particelle
  static void AddParticleType(const ParticleType *type);

  // Metodo statico per stampare tutti i tipi di particelle
  static void PrintArray();

private:
  // Componenti dell'impulso
  double fPx, fPy, fPz;

  // Indice che punta al tipo di particella
  int fIndex;

  // Array statico per contenere i tipi di particelle
  static std::vector<const ParticleType *> fParticleTypes;

  // Metodo statico per trovare una particella per nome
  static int FindParticle(const std::string &name);
};

#endif // PARTICLE_H