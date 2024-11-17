#include "ParticleType.h"
#include <iostream>

// Costruttore che inizializza il nome, la massa e la carica della particella.
// name: nome della particella
// mass: massa della particella
// charge: carica elettrica della particella
ParticleType::ParticleType(const std::string &name, double mass, int charge)
    : fName(name), fMass(mass), fCharge(charge) {}

// Metodo per ottenere il nome della particella.
// return: nome della particella (fName)
const std::string &ParticleType::GetName() const
{
  return fName;
}

// Metodo per ottenere la massa della particella.
// return: massa della particella (fMass)
double ParticleType::GetMass() const
{
  return fMass;
}

// Metodo per ottenere la carica elettrica della particella.
// return: carica elettrica della particella (fCharge)
int ParticleType::GetCharge() const
{
  return fCharge;
}

// Metodo per stampare le proprietà della particella.
// Stampa il nome, la massa e la carica elettrica della particella
// su standard output.
void ParticleType::Print() const
{
  std::cout << "Particle Name: " << fName
            << "\nMass: " << fMass
            << "\nCharge: " << fCharge
            << std::endl;
}