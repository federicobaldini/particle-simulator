#include "ResonanceType.h"
#include <iostream>

// Definizione del costruttore
ResonanceType::ResonanceType(const std::string &name, double mass, int charge, double width)
    : ParticleType(name, mass, charge), fWidth(width) {}

// Definizione del getter per la larghezza della risonanza
double ResonanceType::GetWidth() const
{
  return fWidth;
}

// Definizione del metodo Print
void ResonanceType::Print() const
{
  ParticleType::Print(); // Chiamata al metodo della classe base
  std::cout << "Width: " << fWidth << std::endl;
}