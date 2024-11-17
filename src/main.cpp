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

// Questo programma simula eventi di collisione tra particelle, generando casualmente le loro proprietà
// (come angoli, quantità di moto e tipi) e calcolando proprietà derivate come energia e massa invariante.
// Utilizza ROOT per la visualizzazione e l'analisi statistica dei risultati mediante istogrammi.
// La simulazione include il decadimento di particelle risonanti (come K*),
// con conservazione della quantità di moto e generazione di prodotti di decadimento.

int main()
{
  // Inizializzazione del generatore di numeri casuali e dei tipi di particelle con proprietà fisiche
  gRandom->SetSeed(12345);
  Particle::AddParticleType("Pion+", 0.13957, 1);
  Particle::AddParticleType("Pion-", 0.13957, -1);
  Particle::AddParticleType("Kaon+", 0.49367, 1);
  Particle::AddParticleType("Kaon-", 0.49367, -1);
  Particle::AddParticleType("Proton+", 0.93827, 1);
  Particle::AddParticleType("Proton-", 0.93827, -1);
  Particle::AddParticleType("K*", 0.89166, 0, 0.050);

  // Creazione degli istogrammi per le proprietà delle particelle
  TH1F *hParticleTypes = new TH1F("hParticleTypes", "Particle Types", 7, 0, 7);
  TH1F *hAzimuthalAngle = new TH1F("hAzimuthalAngle", "Azimuthal Angle Distribution", 100, 0, 2 * M_PI);
  TH1F *hPolarAngle = new TH1F("hPolarAngle", "Polar Angle Distribution", 100, 0, M_PI);
  TH1F *hMomentum = new TH1F("hMomentum", "Momentum Distribution", 100, 0, 5);
  TH1F *hTransverseMomentum = new TH1F("hTransverseMomentum", "Transverse Momentum Distribution", 100, 0, 5);
  TH1F *hEnergy = new TH1F("hEnergy", "Energy Distribution", 100, 0, 5);

  // Istogrammi per le masse invarianti
  TH1F *hInvariantMass = new TH1F("hInvariantMass", "Invariant Mass Distribution (All Pairs)", 1000, 0, 3);
  TH1F *hInvMassOppositeCharge = new TH1F("hInvMassOppositeCharge", "Invariant Mass Opposite Charge", 1000, 0, 3);
  TH1F *hInvMassSameCharge = new TH1F("hInvMassSameCharge", "Invariant Mass Same Charge", 1000, 0, 3);
  TH1F *hInvMassPionKaon = new TH1F("hInvMassPionKaon", "Invariant Mass Pion-Kaon (Opposite Charge)", 1000, 0, 3);
  TH1F *hInvMassPionKaonSC = new TH1F("hInvMassPionKaonSC", "Invariant Mass Pion-Kaon (Same Charge)", 1000, 0, 3);
  TH1F *hInvMassDecayProducts = new TH1F("hInvMassDecayProducts", "Invariant Mass Decay Products (K* daughters)", 1000, 0, 3);

  // Configurazione degli assi per gli istogrammi
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

  // Abilitazione della somma dei pesi al quadrato per gli istogrammi di massa invariante
  hInvariantMass->Sumw2();
  hInvMassOppositeCharge->Sumw2();
  hInvMassSameCharge->Sumw2();
  hInvMassPionKaon->Sumw2();
  hInvMassPionKaonSC->Sumw2();
  hInvMassDecayProducts->Sumw2();

  // Array per memorizzare tutte le particelle generate in un evento.
  // La dimensione è 120 per consentire l'aggiunta di particelle derivate
  // dai decadimenti delle risonanze, che possono aggiungere fino a 20 particelle extra.
  Particle EventParticles[120];

  // Generazione di 100.000 eventi di collisione, ciascuno contenente 100 particelle iniziali.
  for (int event = 0; event < 100000; ++event)
  {
    // Conta il numero di particelle totali nell'evento, inizialmente 100.
    // Questo contatore aumenta con l'aggiunta di prodotti di decadimento.
    int particleCount = 100;

    // Loop per generare le 100 particelle iniziali in ogni evento.
    for (int i = 0; i < 100; ++i)
    {
      // Generazione casuale di angoli e quantità di moto:
      // - `phi`: angolo azimutale distribuito uniformemente tra 0 e 2π.
      // - `theta`: angolo polare distribuito uniformemente tra 0 e π.
      // - `momentum`: modulo della quantità di moto, distribuito esponenzialmente.
      double phi = gRandom->Uniform(0, 2 * M_PI);
      double theta = gRandom->Uniform(0, M_PI);
      double momentum = gRandom->Exp(1);

      // Conversione delle coordinate angolari in coordinate cartesiane (Px, Py, Pz).
      double px = momentum * sin(theta) * cos(phi);
      double py = momentum * sin(theta) * sin(phi);
      double pz = momentum * cos(theta);

      // Determinazione casuale del tipo di particella in base a probabilità prefissate.
      double randType = gRandom->Rndm();
      if (randType < 0.4)
        EventParticles[i].SetParticleTypeIndex("Pion+"); // 40% probabilità
      else if (randType < 0.8)
        EventParticles[i].SetParticleTypeIndex("Pion-"); // 40% probabilità
      else if (randType < 0.85)
        EventParticles[i].SetParticleTypeIndex("Kaon+"); // 5% probabilità
      else if (randType < 0.9)
        EventParticles[i].SetParticleTypeIndex("Kaon-"); // 5% probabilità
      else if (randType < 0.945)
        EventParticles[i].SetParticleTypeIndex("Proton+"); // 4.5% probabilità
      else if (randType < 0.99)
        EventParticles[i].SetParticleTypeIndex("Proton-"); // 4.5% probabilità
      else
      {
        // Caso in cui si genera una risonanza K* (1% probabilità).
        EventParticles[i].SetParticleTypeIndex("K*");
        EventParticles[i].SetPulse(px, py, pz);

        // Creazione delle particelle figlie (pione e kaone) per il decadimento della risonanza.
        Particle pion;
        Particle kaon;

        // Assegnazione casuale della carica al pione e al kaone.
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

        // Esecuzione del decadimento della K* in pion e kaon.
        // Se il decadimento è riuscito, i prodotti sono aggiunti all'array di particelle.
        if (EventParticles[i].Decay2Body(pion, kaon) == 0)
        {
          EventParticles[particleCount++] = pion;
          EventParticles[particleCount++] = kaon;
        }

        // Passa alla particella successiva poiché la risonanza è già decaduta.
        // continue;
      }

      // Imposta la quantità di moto della particella generata.
      EventParticles[i].SetPulse(px, py, pz);

      // Riempimento degli istogrammi con le proprietà della particella generata.
      hParticleTypes->Fill(EventParticles[i].GetParticleTypeIndex());
      hAzimuthalAngle->Fill(phi);
      hPolarAngle->Fill(theta);
      hMomentum->Fill(momentum);
      hTransverseMomentum->Fill(sqrt(px * px + py * py)); // Momento trasversale
      hEnergy->Fill(EventParticles[i].GetEnergy());       // Energia totale
    }

    // Numero totale di particelle nell'evento, incluse quelle da decadimenti.
    int totalParticles = particleCount;

    // Riempimento degli istogrammi per le particelle aggiunte dopo i decadimenti.
    for (int i = 100; i < totalParticles; ++i)
    {
      hParticleTypes->Fill(EventParticles[i].GetParticleTypeIndex());
      double px = EventParticles[i].GetPulseX();
      double py = EventParticles[i].GetPulseY();
      double pz = EventParticles[i].GetPulseZ();
      double momentum = sqrt(px * px + py * py + pz * pz);
      double pt = sqrt(px * px + py * py);
      hMomentum->Fill(momentum);                    // Quantità di moto
      hTransverseMomentum->Fill(pt);                // Quantità di moto trasversale
      hEnergy->Fill(EventParticles[i].GetEnergy()); // Energia
    }

    // Calcolo delle masse invarianti tra tutte le coppie di particelle dell'evento.
    for (int i = 0; i < totalParticles; ++i)
    {
      for (int j = i + 1; j < totalParticles; ++j)
      {
        double invMass = EventParticles[i].InvariantMass(EventParticles[j]);

        // Riempimento dell'istogramma per tutte le masse invarianti.
        hInvariantMass->Fill(invMass);

        const ParticleType *particleTypeI = Particle::GetParticleType(EventParticles[i].GetParticleTypeIndex());
        const ParticleType *particleTypeJ = Particle::GetParticleType(EventParticles[j].GetParticleTypeIndex());

        if (particleTypeI && particleTypeJ)
        {
          // Se la coppia ha carica opposta.
          if (particleTypeI->GetCharge() * particleTypeJ->GetCharge() < 0)
            hInvMassOppositeCharge->Fill(invMass);

          // Se la coppia ha la stessa carica.
          if (particleTypeI->GetCharge() * particleTypeJ->GetCharge() > 0)
            hInvMassSameCharge->Fill(invMass);

          // Masse invarianti tra Pion+/Kaon- e Pion-/Kaon+.
          if ((particleTypeI->GetName() == "Pion+" && particleTypeJ->GetName() == "Kaon-") ||
              (particleTypeI->GetName() == "Pion-" && particleTypeJ->GetName() == "Kaon+"))
          {
            hInvMassPionKaon->Fill(invMass);
          }

          // Masse invarianti tra Pion+/Kaon+ e Pion-/Kaon-.
          if ((particleTypeI->GetName() == "Pion+" && particleTypeJ->GetName() == "Kaon+") ||
              (particleTypeI->GetName() == "Pion-" && particleTypeJ->GetName() == "Kaon-"))
          {
            hInvMassPionKaonSC->Fill(invMass);
          }

          // Masse invarianti tra prodotti di decadimento della stessa K*.
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

  // Salvataggio degli istogrammi su file ROOT per analisi
  TFile file("root/data/ParticleAnalysis.root", "RECREATE");
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