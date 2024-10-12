#ifndef RESONANCETYPE_H
#define RESONANCETYPE_H

#include "ParticleType.h"

// Classe che eredita da ParticleType e aggiunge la larghezza per particelle instabili
class ResonanceType : public ParticleType
{
public:
  // Costruttore con parametri di base e larghezza della risonanza
  ResonanceType(const std::string &name, double mass, int charge, double width);

  // Metodo per ottenere la larghezza della risonanza
  double GetWidth() const;

  // Metodo per stampare i dettagli della particella risonante
  void Print() const override;

private:
  // Larghezza della risonanza
  double fWidth;
};

#endif // RESONANCETYPE_H