#include "ParticleType.h"
#include <iostream>

// Constructor initializes particle name, mass, and charge
ParticleType::ParticleType(const std::string &name, double mass, int charge)
    : fName(name), fMass(mass), fCharge(charge) {}

// Returns particle name
const std::string &ParticleType::GetName() const
{
  return fName;
}

// Returns particle mass
double ParticleType::GetMass() const
{
  return fMass;
}

// Returns particle charge
int ParticleType::GetCharge() const
{
  return fCharge;
}

// Prints particle properties to standard output
void ParticleType::Print() const
{
  std::cout << "Particle Name: " << fName
            << "\nMass: " << fMass
            << "\nCharge: " << fCharge
            << std::endl;
}