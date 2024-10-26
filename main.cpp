#include "ParticleType.h"
#include "ResonanceType.h"
#include "Particle.h"
#include <iostream>
#include <vector>
#include <cmath>
#include "TH1F.h"
#include "TFile.h"
#include "TRandom.h"
#include "TCanvas.h"

int main()
{
  // Punto 0: Inizializzazione del seed e aggiunta dei tipi di particelle
  gRandom->SetSeed(12345);
  Particle::AddParticleType("Pion+", 0.13957, 1);
  Particle::AddParticleType("Pion-", 0.13957, -1);
  Particle::AddParticleType("Kaon+", 0.49367, 1);
  Particle::AddParticleType("Kaon-", 0.49367, -1);
  Particle::AddParticleType("Proton+", 0.93827, 1);
  Particle::AddParticleType("Proton-", 0.93827, -1);
  Particle::AddParticleType("K*", 0.89166, 0, 0.050); // Risonanza K*

  // Definizione degli istogrammi
  TH1F *hParticleTypes = new TH1F("hParticleTypes", "Particle Types", 7, 0, 7);
  TH1F *hAzimuthalAngle = new TH1F("hAzimuthalAngle", "Azimuthal Angle Distribution", 100, 0, 2 * M_PI);
  TH1F *hPolarAngle = new TH1F("hPolarAngle", "Polar Angle Distribution", 100, 0, M_PI);
  TH1F *hMomentum = new TH1F("hMomentum", "Momentum Distribution", 100, 0, 5);
  TH1F *hTransverseMomentum = new TH1F("hTransverseMomentum", "Transverse Momentum Distribution", 100, 0, 5);
  TH1F *hEnergy = new TH1F("hEnergy", "Energy Distribution", 100, 0, 5);
  TH1F *hInvariantMass = new TH1F("hInvariantMass", "Invariant Mass Distribution", 100, 0, 3);

  // Abilitare la valutazione delle incertezze
  hInvariantMass->Sumw2();

  // Evento con array di particelle: dimensione scelta in base alla probabilità di decadimento K*
  Particle EventParticles[120];
  std::vector<Particle> finalParticles;

  // Ciclo principale su 100.000 eventi
  for (int event = 0; event < 100000; ++event)
  {
    finalParticles.clear(); // Svuotare il vettore per ogni nuovo evento

    for (int i = 0; i < 100; ++i)
    {
      double phi = gRandom->Uniform(0, 2 * M_PI);
      double theta = gRandom->Uniform(0, M_PI);
      double momentum = gRandom->Exp(1);

      double px = momentum * sin(theta) * cos(phi);
      double py = momentum * sin(theta) * sin(phi);
      double pz = momentum * cos(theta);

      // Generazione casuale del tipo di particella con le proporzioni richieste
      double randType = gRandom->Rndm();
      if (randType < 0.4)
      {
        EventParticles[i].SetParticleTypeIndex("Pion+");
      }
      else if (randType < 0.8)
      {
        EventParticles[i].SetParticleTypeIndex("Pion-");
      }
      else if (randType < 0.9)
      {
        EventParticles[i].SetParticleTypeIndex("Kaon+");
      }
      else if (randType < 0.91)
      {
        EventParticles[i].SetParticleTypeIndex("Kaon-");
      }
      else if (randType < 0.955)
      {
        EventParticles[i].SetParticleTypeIndex("Proton+");
      }
      else if (randType < 0.965)
      {
        EventParticles[i].SetParticleTypeIndex("Proton-");
      }
      else
      {
        EventParticles[i].SetParticleTypeIndex("K*");
        Particle pion("Pion+");
        Particle kaon("Kaon-");

        if (gRandom->Rndm() < 0.5)
        {
          pion.SetParticleTypeIndex("Pion-");
          kaon.SetParticleTypeIndex("Kaon+");
        }

        if (EventParticles[i].Decay2Body(pion, kaon) == 0)
        {
          finalParticles.push_back(pion);
          finalParticles.push_back(kaon);
        }
      }

      // Impostare l'impulso della particella
      EventParticles[i].SetPulse(px, py, pz);
      finalParticles.push_back(EventParticles[i]);

      // Riempire gli istogrammi per il tipo, angoli, impulso, ecc.
      hParticleTypes->Fill(EventParticles[i].GetParticleTypeIndex());
      hAzimuthalAngle->Fill(phi);
      hPolarAngle->Fill(theta);
      hMomentum->Fill(momentum);
      hTransverseMomentum->Fill(sqrt(px * px + py * py));
      hEnergy->Fill(EventParticles[i].GetEnergy());
    }

    // Calcolo della massa invariante tra tutte le particelle finali
    for (size_t i = 0; i < finalParticles.size(); ++i)
    {
      for (size_t j = i + 1; j < finalParticles.size(); ++j)
      {
        double invMass = finalParticles[i].InvariantMass(finalParticles[j]);
        hInvariantMass->Fill(invMass);
      }
    }
  }

  // Salvataggio degli istogrammi in un file ROOT
  TFile file("ParticleAnalysis.root", "RECREATE");
  hParticleTypes->Write();
  hAzimuthalAngle->Write();
  hPolarAngle->Write();
  hMomentum->Write();
  hTransverseMomentum->Write();
  hEnergy->Write();
  hInvariantMass->Write();
  file.Close();

  std::cout << "Istogrammi salvati in ParticleAnalysis.root" << std::endl;

  return 0;
}