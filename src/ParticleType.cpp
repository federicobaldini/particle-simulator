#include "ParticleType.h"
#include <iostream>

ParticleType::ParticleType(const std::string &name, double mass, int charge)
    : fName(name), fMass(mass), fCharge(charge) {}

const std::string &ParticleType::GetName() const
{
  return fName;
}

double ParticleType::GetMass() const
{
  return fMass;
}

int ParticleType::GetCharge() const
{
  return fCharge;
}

void ParticleType::Print() const
{
  std::cout << "Particle Name: " << fName
            << "\nMass: " << fMass
            << "\nCharge: " << fCharge
            << std::endl;
}