#include "Particle.h"
#include <iostream>
#include <cmath>

// Inizializzazione dell'array statico dei tipi di particelle
std::vector<const ParticleType *> Particle::fParticleTypes;

// Costruttore parametrico
Particle::Particle(double px, double py, double pz, int index)
    : fPx(px), fPy(py), fPz(pz), fIndex(index) {}

// Metodo per ottenere l'indice
int Particle::GetIndex() const
{
  return fIndex;
}

// Metodo per impostare l'indice
void Particle::SetIndex(int index)
{
  fIndex = index;
}

// Metodo per impostare l'impulso
void Particle::SetP(double px, double py, double pz)
{
  fPx = px;
  fPy = py;
  fPz = pz;
}

// Metodo statico per aggiungere tipi di particelle
void Particle::AddParticleType(const ParticleType *type)
{
  fParticleTypes.push_back(type);
}

// Metodo per stampare tutti i tipi di particelle
void Particle::PrintArray()
{
  for (const auto &type : fParticleTypes)
  {
    type->Print();
  }
}

// Metodo privato per trovare una particella in base al nome
int Particle::FindParticle(const std::string &name)
{
  for (size_t i = 0; i < fParticleTypes.size(); ++i)
  {
    if (fParticleTypes[i]->GetName() == name)
    {
      return i;
    }
  }
  return -1; // Non trovato
}