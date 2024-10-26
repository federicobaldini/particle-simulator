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
  TH1F *hInvariantMass = new TH1F("hInvariantMass", "Invariant Mass Distribution", 100, 0, 3);

  // Enable error calculation for invariant mass histogram
  hInvariantMass->Sumw2();

  // Define an array of particles per event, with extra capacity for decayed particles
  Particle EventParticles[120];
  std::vector<Particle> finalParticles;

  // Generate 100,000 events with 100 particles each
  for (int event = 0; event < 100000; ++event)
  {
    finalParticles.clear();

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
      else if (randType < 0.9)
        EventParticles[i].SetParticleTypeIndex("Kaon+");
      else if (randType < 0.91)
        EventParticles[i].SetParticleTypeIndex("Kaon-");
      else if (randType < 0.955)
        EventParticles[i].SetParticleTypeIndex("Proton+");
      else if (randType < 0.965)
        EventParticles[i].SetParticleTypeIndex("Proton-");
      else
      {
        EventParticles[i].SetParticleTypeIndex("K*");
        Particle pion("Pion+");
        Particle kaon("Kaon-");

        // Randomly assign pion and kaon charge for decay products
        if (gRandom->Rndm() < 0.5)
        {
          pion.SetParticleTypeIndex("Pion-");
          kaon.SetParticleTypeIndex("Kaon+");
        }

        // Perform decay and store decay products
        if (EventParticles[i].Decay2Body(pion, kaon) == 0)
        {
          finalParticles.push_back(pion);
          finalParticles.push_back(kaon);
        }
      }

      // Set particle momentum
      EventParticles[i].SetPulse(px, py, pz);
      finalParticles.push_back(EventParticles[i]);

      // Fill histograms for particle properties
      hParticleTypes->Fill(EventParticles[i].GetParticleTypeIndex());
      hAzimuthalAngle->Fill(phi);
      hPolarAngle->Fill(theta);
      hMomentum->Fill(momentum);
      hTransverseMomentum->Fill(sqrt(px * px + py * py));
      hEnergy->Fill(EventParticles[i].GetEnergy());
    }

    // Calculate invariant mass between pairs of final particles
    for (size_t i = 0; i < finalParticles.size(); ++i)
    {
      for (size_t j = i + 1; j < finalParticles.size(); ++j)
      {
        double invMass = finalParticles[i].InvariantMass(finalParticles[j]);
        hInvariantMass->Fill(invMass);
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
  file.Close();

  std::cout << "Histograms saved to ParticleAnalysis.root" << std::endl;

  return 0;
}