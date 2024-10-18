#include "ParticleType.h"
#include "ResonanceType.h"
#include "Particle.h"
#include <iostream>

int main()
{
  // Aggiungi nuovi tipi di particelle al sistema
  Particle::AddParticleType("Electron", 0.000511, -1); // Massa in GeV/c^2
  Particle::AddParticleType("Proton", 0.938, 1);       // Massa in GeV/c^2
  Particle::AddParticleType("Pion", 0.139, 1);         // Massa in GeV/c^2
  Particle::AddParticleType("Rho", 0.770, 0, 0.150);   // Risonanza, con larghezza

  // Creazione di particelle e impostazione degli impulsi
  Particle p1("Electron", 1.0, 0.0, 0.0); // Particella con impulso (1, 0, 0)
  Particle p2("Proton", 0.0, 1.0, 0.0);   // Particella con impulso (0, 1, 0)
  Particle p3("Pion", 0.0, 0.0, 1.0);     // Particella con impulso (0, 0, 1)
  Particle p4("Rho", 0.5, 0.5, 0.5);      // Risonanza con impulso (0.5, 0.5, 0.5)

  // Stampa le proprietà di ciascuna particella
  std::cout << "Properties of p1 (Electron):" << std::endl;
  p1.Print();
  std::cout << std::endl;

  std::cout << "Properties of p2 (Proton):" << std::endl;
  p2.Print();
  std::cout << std::endl;

  std::cout << "Properties of p3 (Pion):" << std::endl;
  p3.Print();
  std::cout << std::endl;

  std::cout << "Properties of p4 (Rho Resonance):" << std::endl;
  p4.Print();
  std::cout << std::endl;

  // Calcola e stampa l'energia totale di ciascuna particella
  std::cout << "Energy of p1 (Electron): " << p1.GetEnergy() << " GeV" << std::endl;
  std::cout << "Energy of p2 (Proton): " << p2.GetEnergy() << " GeV" << std::endl;
  std::cout << "Energy of p3 (Pion): " << p3.GetEnergy() << " GeV" << std::endl;
  std::cout << "Energy of p4 (Rho Resonance): " << p4.GetEnergy() << " GeV" << std::endl;

  // Calcola e stampa la massa invariante tra due particelle
  std::cout << "\nInvariant mass between p1 (Electron) and p2 (Proton): "
            << p1.InvMass(p2) << " GeV/c^2" << std::endl;

  std::cout << "Invariant mass between p3 (Pion) and p4 (Rho Resonance): "
            << p3.InvMass(p4) << " GeV/c^2" << std::endl;

  return 0;
}