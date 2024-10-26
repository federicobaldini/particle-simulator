#ifndef PARTICLE_H
#define PARTICLE_H

#include "ParticleType.h"
#include <string>

class Particle
{
private:
  static ParticleType *fParticleType[];
  static const int fMaxNumParticleType = 10;
  static int fNParticleType;

  int fIndex;
  double fPx, fPy, fPz;

  static int FindParticleType(const std::string &name);

  // Metodo privato per applicare il boost
  void Boost(double bx, double by, double bz);

public:
  Particle();
  Particle(const std::string &name, double px = 0, double py = 0, double pz = 0);

  int GetParticleTypeIndex() const;
  double GetPulseX() const { return fPx; }
  double GetPulseY() const { return fPy; }
  double GetPulseZ() const { return fPz; }

  static void AddParticleType(const std::string &name, double mass, int charge, double width = 0);

  void SetParticleTypeIndex(const std::string &name);
  void SetParticleTypeIndex(int index);

  void Print() const;
  void SetPulse(double px, double py, double pz);
  double GetMass() const;
  double GetEnergy() const;
  double InvariantMass(const Particle &other) const;

  // Nuovo metodo pubblico per la decadenza a due corpi
  int Decay2Body(Particle &dau1, Particle &dau2) const;
};

#endif // PARTICLE_H