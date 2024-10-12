#ifndef PARTICLETYPE_H
#define PARTICLETYPE_H

#include <string>

// Classe per descrivere le particelle stabili
class ParticleType
{
public:
  // Costruttore con parametri di base
  ParticleType(const std::string &name, double mass, int charge);

  // Metodi per ottenere i valori degli attributi
  const std::string &GetName() const; // Restituisce il nome
  double GetMass() const;             // Restituisce la massa
  int GetCharge() const;              // Restituisce la carica

  // Metodo per stampare i dettagli della particella
  virtual void Print() const;

protected:
  // Attributi base della particella
  std::string fName;
  double fMass;
  int fCharge;
};

#endif // PARTICLETYPE_H