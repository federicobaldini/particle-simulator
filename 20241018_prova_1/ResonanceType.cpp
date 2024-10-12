#include "ResonanceType.h"
#include <iostream>

// Definizione del costruttore di ResonanceType
ResonanceType::ResonanceType(const std::string &name, double mass, int charge, double width)
    : ParticleType(name, mass, charge), fWidth(width) {}

// Definizione del metodo Print
void ResonanceType::Print() const
{
  ParticleType::Print(); // Chiama il metodo della classe base
  std::cout << "Width: " << fWidth << std::endl;
}