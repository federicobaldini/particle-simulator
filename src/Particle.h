#ifndef PARTICLE_H
#define PARTICLE_H

#include "ParticleType.h"
#include <string>

class Particle
{
private:
  // Static array for storing particle types
  static ParticleType *fParticleType[];
  static const int fMaxNumParticleType = 10;
  static int fNParticleType;

  int fIndex;           // Index for particle type
  double fPx, fPy, fPz; // Momentum components

  // Finds particle type by name, returning its index
  static int FindParticleType(const std::string &name);

  // Applies a relativistic boost to particle momentum
  void Boost(double bx, double by, double bz);

public:
  Particle(); // Default constructor
  Particle(const std::string &name, double px = 0, double py = 0, double pz = 0);

  // Returns particle type index
  int GetParticleTypeIndex() const;

  // Statuic method for get the particle type by index
  static const ParticleType *GetParticleType(int index);

  // Getters for momentum components
  double GetPulseX() const { return fPx; }
  double GetPulseY() const { return fPy; }
  double GetPulseZ() const { return fPz; }

  // Adds a new particle type to the system
  static void AddParticleType(const std::string &name, double mass, int charge, double width = 0);

  // Sets particle type by name or index
  void SetParticleTypeIndex(const std::string &name);
  void SetParticleTypeIndex(int index);

  // Prints particle type and momentum information
  void Print() const;

  // Sets momentum components
  void SetPulse(double px, double py, double pz);

  // Returns the particle mass
  double GetMass() const;

  // Calculates total particle energy
  double GetEnergy() const;

  // Calculates invariant mass with another particle
  double InvariantMass(const Particle &other) const;

  // Simulates decay into two particles
  int Decay2Body(Particle &dau1, Particle &dau2) const;
};

#endif // PARTICLE_H