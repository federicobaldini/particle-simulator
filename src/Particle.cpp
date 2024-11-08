#include "Particle.h"
#include "ResonanceType.h"
#include "ParticleType.h"
#include <iostream>
#include <cmath>
#include <cstdlib>

ParticleType *Particle::fParticleType[Particle::fMaxNumParticleType] = {nullptr};
int Particle::fNParticleType = 0;

// Default constructor initializing momentum components and index
Particle::Particle() : fPx(0), fPy(0), fPz(0), fIndex(-1) {}

// Constructor that sets particle type and initial momentum components
Particle::Particle(const std::string &name, double px, double py, double pz)
    : fPx(px), fPy(py), fPz(pz)
{
  fIndex = FindParticleType(name);
  if (fIndex == -1)
  {
    std::cout << "Particle type " << name << " not found!" << std::endl;
  }
}

// Searches for particle type by name; returns index or -1 if not found
int Particle::FindParticleType(const std::string &name)
{
  for (int i = 0; i < fNParticleType; ++i)
  {
    if (fParticleType[i]->GetName() == name)
    {
      return i;
    }
  }
  return -1;
}

// Returns the index of the particle type
int Particle::GetParticleTypeIndex() const
{
  return fIndex;
}

const ParticleType *Particle::GetParticleType(int index)
{
  if (index >= 0 && index < fNParticleType)
  {
    return fParticleType[index];
  }
  else
  {
    return nullptr;
  }
}

// Adds a new particle type to the static array if within capacity
void Particle::AddParticleType(const std::string &name, double mass, int charge, double width)
{
  if (fNParticleType >= fMaxNumParticleType)
  {
    std::cout << "Cannot add more particle types, maximum reached!" << std::endl;
    return;
  }

  if (FindParticleType(name) != -1)
  {
    std::cout << "Particle type " << name << " already exists!" << std::endl;
    return;
  }

  if (width == 0)
  {
    fParticleType[fNParticleType] = new ParticleType(name, mass, charge);
  }
  else
  {
    fParticleType[fNParticleType] = new ResonanceType(name, mass, charge, width);
  }
  ++fNParticleType;
}

// Sets particle type index by name, or prints an error if not found
void Particle::SetParticleTypeIndex(const std::string &name)
{
  fIndex = FindParticleType(name);
  if (fIndex == -1)
  {
    std::cout << "Particle type " << name << " not found!" << std::endl;
  }
}

// Sets particle type index directly, with bounds checking
void Particle::SetParticleTypeIndex(int index)
{
  if (index >= 0 && index < fNParticleType)
  {
    fIndex = index;
  }
  else
  {
    std::cout << "Invalid particle index!" << std::endl;
  }
}

// Prints particle type information and momentum components
void Particle::Print() const
{
  if (fIndex != -1 && fIndex < fNParticleType)
  {
    fParticleType[fIndex]->Print();
  }
  std::cout << "Px: " << fPx << ", Py: " << fPy << ", Pz: " << fPz << std::endl;
}

// Sets the momentum components
void Particle::SetPulse(double px, double py, double pz)
{
  fPx = px;
  fPy = py;
  fPz = pz;
}

// Returns the particle mass or zero if type index is invalid
double Particle::GetMass() const
{
  return (fIndex != -1) ? fParticleType[fIndex]->GetMass() : 0;
}

// Computes the total energy based on mass and momentum
double Particle::GetEnergy() const
{
  double mass = GetMass();
  double p2 = fPx * fPx + fPy * fPy + fPz * fPz;
  return std::sqrt(mass * mass + p2);
}

// Calculates invariant mass with another particle
double Particle::InvariantMass(const Particle &other) const
{
  double e1 = GetEnergy();
  double e2 = other.GetEnergy();
  double px_total = fPx + other.GetPulseX();
  double py_total = fPy + other.GetPulseY();
  double pz_total = fPz + other.GetPulseZ();
  double p2_total = px_total * px_total + py_total * py_total + pz_total * pz_total;
  return std::sqrt((e1 + e2) * (e1 + e2) - p2_total);
}

// Simulates decay into two daughter particles with momentum conservation
int Particle::Decay2Body(Particle &dau1, Particle &dau2) const
{
  if (GetMass() == 0.0)
  {
    std::cerr << "Decayment cannot be performed if mass is zero\n";
    return 1;
  }

  double massMot = GetMass();
  double massDau1 = dau1.GetMass();
  double massDau2 = dau2.GetMass();

  // Adjusts mass with a width effect if particle is a ResonanceType
  if (fIndex > -1)
  {
    ResonanceType *resonance = dynamic_cast<ResonanceType *>(fParticleType[fIndex]);
    if (resonance)
    {
      float x1, x2, w, y1;
      double invnum = 1. / RAND_MAX;
      do
      {
        x1 = 2.0 * rand() * invnum - 1.0;
        x2 = 2.0 * rand() * invnum - 1.0;
        w = x1 * x1 + x2 * x2;
      } while (w >= 1.0);

      w = sqrt((-2.0 * log(w)) / w);
      y1 = x1 * w;
      massMot += resonance->GetWidth() * y1;
    }
  }

  if (massMot < massDau1 + massDau2)
  {
    std::cerr << "Decayment cannot be performed because mass is too low in this channel\n";
    return 2;
  }

  double pout = sqrt((massMot * massMot - (massDau1 + massDau2) * (massDau1 + massDau2)) *
                     (massMot * massMot - (massDau1 - massDau2) * (massDau1 - massDau2))) /
                (massMot * 0.5);

  double norm = 2 * M_PI / RAND_MAX;
  double phi = rand() * norm;
  double theta = rand() * norm * 0.5 - M_PI / 2.;

  // Assign momentum to decay products in opposite directions
  dau1.SetPulse(pout * sin(theta) * cos(phi), pout * sin(theta) * sin(phi), pout * cos(theta));
  dau2.SetPulse(-pout * sin(theta) * cos(phi), -pout * sin(theta) * sin(phi), -pout * cos(theta));

  double energy = sqrt(fPx * fPx + fPy * fPy + fPz * fPz + massMot * massMot);
  double bx = fPx / energy;
  double by = fPy / energy;
  double bz = fPz / energy;

  // Apply relativistic boost to daughters
  dau1.Boost(bx, by, bz);
  dau2.Boost(bx, by, bz);

  return 0;
}

// Boosts the particle's momentum based on given velocity components
void Particle::Boost(double bx, double by, double bz)
{
  double energy = GetEnergy();
  double b2 = bx * bx + by * by + bz * bz;
  double gamma = 1.0 / sqrt(1.0 - b2);
  double bp = bx * fPx + by * fPy + bz * fPz;
  double gamma2 = (b2 > 0) ? (gamma - 1.0) / b2 : 0.0;

  fPx += gamma2 * bp * bx + gamma * bx * energy;
  fPy += gamma2 * bp * by + gamma * by * energy;
  fPz += gamma2 * bp * bz + gamma * bz * energy;
}