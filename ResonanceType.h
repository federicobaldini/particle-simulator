#ifndef RESONANCETYPE_H
#define RESONANCETYPE_H

#include "ParticleType.h"

class ResonanceType : public ParticleType
{
private:
  const double fWidth; // Resonance width

public:
  // Constructor initializing name, mass, charge, and width
  ResonanceType(const std::string &name, double mass, int charge, double width);

  // Returns the resonance width
  double GetWidth() const override;

  // Prints particle properties, including width
  void Print() const override;
};

#endif // RESONANCETYPE_H