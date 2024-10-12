#include "ParticleType.h"
#include <iostream>

// Definizione del costruttore di ParticleType
ParticleType::ParticleType(const std::string &name, double mass, int charge)
    : fName(name), fMass(mass), fCharge(charge) {}

// Definizione del metodo GetName
const std::string &ParticleType::GetName() const
{
  return fName;
}

// Definizione del metodo Print
void ParticleType::Print() const
{
  std::cout << "Name: " << fName << ", Mass: " << fMass << ", Charge: " << fCharge << std::endl;
}