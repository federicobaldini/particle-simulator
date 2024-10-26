#include "ParticleType.h"
#include "ResonanceType.h"
#include "Particle.h"
#include <iostream>

int main()
{
  // Test const su ParticleType
  const ParticleType electronType("Electron", 0.000511, -1);
  std::cout << "Testing ParticleType (Electron):\n";
  std::cout << "Name: " << electronType.GetName() << "\n";
  std::cout << "Mass: " << electronType.GetMass() << "\n";
  std::cout << "Charge: " << electronType.GetCharge() << "\n";
  electronType.Print();

  // Test const su ResonanceType
  const ResonanceType rhoType("Rho", 0.770, 0, 0.150);
  std::cout << "\nTesting ResonanceType (Rho Resonance):\n";
  std::cout << "Name: " << rhoType.GetName() << "\n";
  std::cout << "Mass: " << rhoType.GetMass() << "\n";
  std::cout << "Charge: " << rhoType.GetCharge() << "\n";
  std::cout << "Width: " << rhoType.GetWidth() << "\n";
  rhoType.Print();

  // --- Test della classe Particle ---

  // Aggiungi nuovi tipi di particelle al sistema
  Particle::AddParticleType("Electron", 0.000511, -1); // Massa in GeV/c^2
  Particle::AddParticleType("Proton", 0.938, 1);       // Massa in GeV/c^2
  Particle::AddParticleType("Pion", 0.139, 1);         // Massa in GeV/c^2
  Particle::AddParticleType("Rho", 0.770, 0, 0.150);   // Risonanza, con larghezza

  // Verifica del metodo AddParticleType e prevenzione di duplicati
  std::cout << "\nAttempting to add duplicate ParticleType (Electron):\n";
  Particle::AddParticleType("Electron", 0.000511, -1); // Questo dovrebbe stampare un messaggio di avviso

  // Creazione di particelle e impostazione degli impulsi
  Particle p1("Electron", 1.0, 0.0, 0.0); // Particella con impulso (1, 0, 0)
  Particle p2("Proton", 0.0, 1.0, 0.0);   // Particella con impulso (0, 1, 0)
  Particle p3("Pion", 0.0, 0.0, 1.0);     // Particella con impulso (0, 0, 1)
  Particle p4("Rho", 0.5, 0.5, 0.5);      // Risonanza con impulso (0.5, 0.5, 0.5)

  // Stampa le proprietà di ciascuna particella
  std::cout << "\nProperties of p1 (Electron):" << std::endl;
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
            << p1.InvariantMass(p2) << " GeV/c^2" << std::endl;

  std::cout << "Invariant mass between p3 (Pion) and p4 (Rho Resonance): "
            << p3.InvariantMass(p4) << " GeV/c^2" << std::endl;

  return 0;
}