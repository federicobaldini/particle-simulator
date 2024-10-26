#ifndef PARTICLETYPE_H
#define PARTICLETYPE_H

#include <iostream>
#include <string>

class ParticleType
{
private:
  const std::string fName; // Particle name
  const double fMass;      // Particle mass
  const int fCharge;       // Particle charge

public:
  // Parameterized constructor
  ParticleType(const std::string &name, double mass, int charge);

  // Accessors for particle properties
  const std::string &GetName() const;
  double GetMass() const;
  int GetCharge() const;

  // Virtual method for particle width, returns 0 for stable particles
  virtual double GetWidth() const { return 0.0; }

  // Prints particle properties
  virtual void Print() const;
};

#endif // PARTICLETYPE_H