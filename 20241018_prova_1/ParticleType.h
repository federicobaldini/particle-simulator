#ifndef PARTICLETYPE_H
#define PARTICLETYPE_H

#include <iostream>
#include <string>

class ParticleType
{
private:
  const std::string fName; // Nome della particella
  const double fMass;      // Massa della particella
  const int fCharge;       // Carica della particella

public:
  // Costruttore parametrico (dichiarazione, non definizione)
  ParticleType(const std::string &name, double mass, int charge);

  // Getters (dichiarazione, non definizione)
  const std::string &GetName() const;
  double GetMass() const;
  int GetCharge() const;

  // Metodo virtuale per la larghezza, ritorna 0 per le particelle stabili
  virtual double GetWidth() const { return 0.0; }

  // Metodo per stampare le proprietà della particella (dichiarazione, non definizione)
  virtual void Print() const;
};

#endif // PARTICLETYPE_H