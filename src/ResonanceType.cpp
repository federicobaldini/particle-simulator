#include "ResonanceType.h"
#include <iostream>

// Constructor initializing base properties and resonance width
ResonanceType::ResonanceType(const std::string &name, double mass, int charge, double width)
    : ParticleType(name, mass, charge), fWidth(width) {}

// Returns resonance width
double ResonanceType::GetWidth() const
{
  return fWidth;
}

// Prints particle properties, including resonance width
void ResonanceType::Print() const
{
  ParticleType::Print(); // Call to base class method
  std::cout << "Width: " << fWidth << std::endl;
}