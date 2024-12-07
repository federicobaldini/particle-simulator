#ifndef RESONANCETYPE_H
#define RESONANCETYPE_H

#include "ParticleType.h"

// La classe ResonanceType rappresenta un tipo di particella che include
// una larghezza di risonanza, estendendo le proprietà della classe base ParticleType.

class ResonanceType : public ParticleType
{
private:
  const double fWidth; // Larghezza della risonanza (caratteristica esclusiva di questo tipo di particella)

public:
  // Costruttore che inizializza il nome, la massa, la carica e la larghezza della risonanza.
  // name: nome della particella
  // mass: massa della particella
  // charge: carica elettrica della particella
  // width: larghezza della risonanza
  ResonanceType(const std::string &name, double mass, int charge, double width);

  // Metodo per accedere alla larghezza di risonanza.
  // return: larghezza di risonanza (fWidth)
  double GetWidth() const override;

  // Metodo per stampare le proprietà della particella, inclusa la larghezza di risonanza.
  // Stampa nome, massa, carica e la larghezza della risonanza.
  void Print() const override;
};

#endif // RESONANCETYPE_H