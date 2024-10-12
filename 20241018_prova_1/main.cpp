#include "Particle.h"
#include "ResonanceType.h"
#include <iostream>

int main()
{
  // Aggiunta dei tipi di particelle
  Particle::AddParticleType(new ParticleType("Pion+", 0.139, +1));
  Particle::AddParticleType(new ParticleType("Pion-", 0.139, -1));
  Particle::AddParticleType(new ResonanceType("K*", 0.892, 0, 0.05));

  // Stampa dei tipi di particelle
  Particle::PrintArray();

  // Crea una particella
  Particle p1(1.0, 2.0, 3.0, 0);  // Pion+
  Particle p2(0.5, 1.5, -0.5, 2); // K*

  // Test di impulso e indice
  p1.SetP(5.0, 5.0, 5.0);
  std::cout << "Index: " << p1.GetIndex() << std::endl;

  return 0;
}