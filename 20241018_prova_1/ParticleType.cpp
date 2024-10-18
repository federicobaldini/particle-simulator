#include "ParticleType.h"
#include <iostream>

// Definizione del costruttore
ParticleType::ParticleType(const std::string &name, double mass, int charge)
    : fName(name), fMass(mass), fCharge(charge) {}

// Definizione del getter per il nome
const std::string &ParticleType::GetName() const
{
  return fName;
}

// Definizione del getter per la massa
double ParticleType::GetMass() const
{
  return fMass;
}

// Definizione del getter per la carica
int ParticleType::GetCharge() const
{
  return fCharge;
}

// Definizione del metodo Print
void ParticleType::Print() const
{
  std::cout << "Particle Name: " << fName
            << "\nMass: " << fMass
            << "\nCharge: " << fCharge
            << std::endl;
}