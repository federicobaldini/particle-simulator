#ifndef RESONANCETYPE_H
#define RESONANCETYPE_H

#include "ParticleType.h"

class ResonanceType : public ParticleType
{
private:
  const double fWidth; // Larghezza della risonanza

public:
  // Costruttore parametrico (dichiarazione, non definizione)
  ResonanceType(const std::string &name, double mass, int charge, double width);

  // Getter per la larghezza della risonanza (dichiarazione, non definizione)
  double GetWidth() const;

  // Metodo per stampare le proprietà della particella (dichiarazione, non definizione)
  void Print() const override;
};

#endif // RESONANCETYPE_H