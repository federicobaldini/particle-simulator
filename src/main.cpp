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

// Il programma simula la generazione di eventi di collisione tra particelle,
// calcolando le loro proprietà come impulso, energia, angoli di distribuzione,
// e la massa invariante tra coppie di particelle.
// Include un meccanismo per far decadere le risonanze (come K*)
// e salvare le proprietà delle particelle figlie.
// Gli istogrammi generati forniscono insight sulla distribuzione dei tipi di particelle,
// impulso trasverso, e altre caratteristiche rilevanti per l'analisi dei decadimenti.

int main()
{
  // Initialize random seed and particle types with properties
  gRandom->SetSeed(12345);
  Particle::AddParticleType("Pion+", 0.13957, 1);
  Particle::AddParticleType("Pion-", 0.13957, -1);
  Particle::AddParticleType("Kaon+", 0.49367, 1);
  Particle::AddParticleType("Kaon-", 0.49367, -1);
  Particle::AddParticleType("Proton+", 0.93827, 1);
  Particle::AddParticleType("Proton-", 0.93827, -1);
  Particle::AddParticleType("K*", 0.89166, 0, 0.050);

  // Define histograms for particle properties and invariant mass
  TH1F *hParticleTypes = new TH1F("hParticleTypes", "Particle Types", 7, 0, 7);
  TH1F *hAzimuthalAngle = new TH1F("hAzimuthalAngle", "Azimuthal Angle Distribution", 100, 0, 2 * M_PI);
  TH1F *hPolarAngle = new TH1F("hPolarAngle", "Polar Angle Distribution", 100, 0, M_PI);
  TH1F *hMomentum = new TH1F("hMomentum", "Momentum Distribution", 100, 0, 5);
  TH1F *hTransverseMomentum = new TH1F("hTransverseMomentum", "Transverse Momentum Distribution", 100, 0, 5);
  TH1F *hEnergy = new TH1F("hEnergy", "Energy Distribution", 100, 0, 5);

  // Histograms for invariant masses
  TH1F *hInvariantMass = new TH1F("hInvariantMass", "Invariant Mass Distribution (All Pairs)", 1000, 0, 3);
  TH1F *hInvMassOppositeCharge = new TH1F("hInvMassOppositeCharge", "Invariant Mass Opposite Charge", 1000, 0, 3);
  TH1F *hInvMassSameCharge = new TH1F("hInvMassSameCharge", "Invariant Mass Same Charge", 1000, 0, 3);
  TH1F *hInvMassPionKaon = new TH1F("hInvMassPionKaon", "Invariant Mass Pion-Kaon (Opposite Charge)", 1000, 0, 3);
  TH1F *hInvMassPionKaonSC = new TH1F("hInvMassPionKaonSC", "Invariant Mass Pion-Kaon (Same Charge)", 1000, 0, 3);
  TH1F *hInvMassDecayProducts = new TH1F("hInvMassDecayProducts", "Invariant Mass Decay Products (K* daughters)", 1000, 0, 3);

  // Set axis labels for histograms
  hParticleTypes->GetXaxis()->SetTitle("Particle Type Index");
  hParticleTypes->GetYaxis()->SetTitle("Counts");

  hAzimuthalAngle->GetXaxis()->SetTitle("Azimuthal Angle (rad)");
  hAzimuthalAngle->GetYaxis()->SetTitle("Counts");

  hPolarAngle->GetXaxis()->SetTitle("Polar Angle (rad)");
  hPolarAngle->GetYaxis()->SetTitle("Counts");

  hMomentum->GetXaxis()->SetTitle("Momentum (GeV/c)");
  hMomentum->GetYaxis()->SetTitle("Counts");

  hTransverseMomentum->GetXaxis()->SetTitle("Transverse Momentum (GeV/c)");
  hTransverseMomentum->GetYaxis()->SetTitle("Counts");

  hEnergy->GetXaxis()->SetTitle("Energy (GeV)");
  hEnergy->GetYaxis()->SetTitle("Counts");

  hInvariantMass->GetXaxis()->SetTitle("Invariant Mass (GeV/c^{2})");
  hInvariantMass->GetYaxis()->SetTitle("Counts");

  hInvMassOppositeCharge->GetXaxis()->SetTitle("Invariant Mass (GeV/c^{2})");
  hInvMassOppositeCharge->GetYaxis()->SetTitle("Counts");

  hInvMassSameCharge->GetXaxis()->SetTitle("Invariant Mass (GeV/c^{2})");
  hInvMassSameCharge->GetYaxis()->SetTitle("Counts");

  hInvMassPionKaon->GetXaxis()->SetTitle("Invariant Mass (GeV/c^{2})");
  hInvMassPionKaon->GetYaxis()->SetTitle("Counts");

  hInvMassPionKaonSC->GetXaxis()->SetTitle("Invariant Mass (GeV/c^{2})");
  hInvMassPionKaonSC->GetYaxis()->SetTitle("Counts");

  hInvMassDecayProducts->GetXaxis()->SetTitle("Invariant Mass (GeV/c^{2})");
  hInvMassDecayProducts->GetYaxis()->SetTitle("Counts");

  // Enable error calculation for invariant mass histograms
  hInvariantMass->Sumw2();
  hInvMassOppositeCharge->Sumw2();
  hInvMassSameCharge->Sumw2();
  hInvMassPionKaon->Sumw2();
  hInvMassPionKaonSC->Sumw2();
  hInvMassDecayProducts->Sumw2();

  // Define an array of particles per event, with extra capacity for decayed particles
  Particle EventParticles[120];

  // Generate 100,000 events with 100 particles each
  for (int event = 0; event < 100000; ++event)
  {
    int particleCount = 100; // Index for EventParticles

    // Generate 100 particles per event
    for (int i = 0; i < 100; ++i)
    {
      // Generate azimuthal angle, polar angle, and momentum
      double phi = gRandom->Uniform(0, 2 * M_PI);
      double theta = gRandom->Uniform(0, M_PI);
      double momentum = gRandom->Exp(1);

      // Convert to Cartesian coordinates
      double px = momentum * sin(theta) * cos(phi);
      double py = momentum * sin(theta) * sin(phi);
      double pz = momentum * cos(theta);

      // Assign particle type based on random distribution
      double randType = gRandom->Rndm();
      if (randType < 0.4)
        EventParticles[i].SetParticleTypeIndex("Pion+");
      else if (randType < 0.8)
        EventParticles[i].SetParticleTypeIndex("Pion-");
      else if (randType < 0.85)
        EventParticles[i].SetParticleTypeIndex("Kaon+");
      else if (randType < 0.9)
        EventParticles[i].SetParticleTypeIndex("Kaon-");
      else if (randType < 0.945)
        EventParticles[i].SetParticleTypeIndex("Proton+");
      else if (randType < 0.99)
        EventParticles[i].SetParticleTypeIndex("Proton-");
      else
      {
        EventParticles[i].SetParticleTypeIndex("K*");

        // Set the momentum of the K*
        EventParticles[i].SetPulse(px, py, pz);

        // Create daughter particles
        Particle pion;
        Particle kaon;

        // Randomly assign pion and kaon charge for decay products
        if (gRandom->Rndm() < 0.5)
        {
          pion.SetParticleTypeIndex("Pion+");
          kaon.SetParticleTypeIndex("Kaon-");
        }
        else
        {
          pion.SetParticleTypeIndex("Pion-");
          kaon.SetParticleTypeIndex("Kaon+");
        }

        // Perform decay and store decay products
        if (EventParticles[i].Decay2Body(pion, kaon) == 0)
        {
          // Add decay products to EventParticles after the 100th element
          EventParticles[particleCount++] = pion;
          EventParticles[particleCount++] = kaon;
        }

        // Continue to the next particle since K* has decayed
        continue;
      }

      // Set particle momentum
      EventParticles[i].SetPulse(px, py, pz);

      // Fill histograms for particle properties
      hParticleTypes->Fill(EventParticles[i].GetParticleTypeIndex());
      hAzimuthalAngle->Fill(phi);
      hPolarAngle->Fill(theta);
      hMomentum->Fill(momentum);
      hTransverseMomentum->Fill(sqrt(px * px + py * py));
      hEnergy->Fill(EventParticles[i].GetEnergy());
    }

    // Collect all particles for this event
    int totalParticles = particleCount;

    // Fill histograms for particles added after the initial loop
    for (int i = 100; i < totalParticles; ++i)
    {
      hParticleTypes->Fill(EventParticles[i].GetParticleTypeIndex());
      double px = EventParticles[i].GetPulseX();
      double py = EventParticles[i].GetPulseY();
      double pz = EventParticles[i].GetPulseZ();
      double momentum = sqrt(px * px + py * py + pz * pz);
      double pt = sqrt(px * px + py * py);
      hMomentum->Fill(momentum);
      hTransverseMomentum->Fill(pt);
      hEnergy->Fill(EventParticles[i].GetEnergy());
    }

    for (int i = 0; i < totalParticles; ++i)
    {
      for (int j = i + 1; j < totalParticles; ++j)
      {
        double invMass = EventParticles[i].InvariantMass(EventParticles[j]);

        // Riempimento dell'istogramma con tutte le masse invarianti
        hInvariantMass->Fill(invMass);

        const ParticleType *particleTypeI = Particle::GetParticleType(EventParticles[i].GetParticleTypeIndex());
        const ParticleType *particleTypeJ = Particle::GetParticleType(EventParticles[j].GetParticleTypeIndex());

        if (particleTypeI && particleTypeJ)
        {
          // Opposite charge
          if (particleTypeI->GetCharge() * particleTypeJ->GetCharge() < 0)
            hInvMassOppositeCharge->Fill(invMass);

          // Same charge
          if (particleTypeI->GetCharge() * particleTypeJ->GetCharge() > 0)
            hInvMassSameCharge->Fill(invMass);

          // Pion+/Kaon- and Pion-/Kaon+
          if ((particleTypeI->GetName() == "Pion+" && particleTypeJ->GetName() == "Kaon-") ||
              (particleTypeI->GetName() == "Pion-" && particleTypeJ->GetName() == "Kaon+"))
          {
            hInvMassPionKaon->Fill(invMass);
          }

          // Pion+/Kaon+ and Pion-/Kaon-
          if ((particleTypeI->GetName() == "Pion+" && particleTypeJ->GetName() == "Kaon+") ||
              (particleTypeI->GetName() == "Pion-" && particleTypeJ->GetName() == "Kaon-"))
          {
            hInvMassPionKaonSC->Fill(invMass);
          }

          // Invariant mass of decay products from the same K*
          if (i >= 100 && j == i + 1)
          {
            if ((particleTypeI->GetName() == "Pion+" && particleTypeJ->GetName() == "Kaon-") ||
                (particleTypeI->GetName() == "Pion-" && particleTypeJ->GetName() == "Kaon+"))
            {
              hInvMassDecayProducts->Fill(invMass);
            }
          }
        }
      }
    }
  }

  // Save histograms to ROOT file for analysis
  TFile file("ParticleAnalysis.root", "RECREATE");
  hParticleTypes->Write();
  hAzimuthalAngle->Write();
  hPolarAngle->Write();
  hMomentum->Write();
  hTransverseMomentum->Write();
  hEnergy->Write();
  hInvariantMass->Write();
  hInvMassOppositeCharge->Write();
  hInvMassSameCharge->Write();
  hInvMassPionKaon->Write();
  hInvMassPionKaonSC->Write();
  hInvMassDecayProducts->Write();
  file.Close();

  std::cout << "Histograms saved to ParticleAnalysis.root" << std::endl;

  return 0;
}