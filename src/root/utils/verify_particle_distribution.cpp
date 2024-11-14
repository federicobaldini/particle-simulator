// verify_particle_distribution.C
// Macro per verificare la distribuzione delle specie di particelle

#include "TFile.h"
#include "TH1F.h"
#include <iostream>

void verify_particle_distribution()
{
  // Specifica le proporzioni teoriche delle particelle (in percentuale)
  const double expectedProportions[] = {
      40.0, // Pion+
      40.0, // Pion-
      5.0,  // Kaon+
      5.0,  // Kaon-
      4.5,  // Proton+
      4.5,  // Proton-
      1.0   // K*
  };
  const int nParticleTypes = sizeof(expectedProportions) / sizeof(expectedProportions[0]);

  // Apri il file ROOT e ottieni l'istogramma delle specie di particelle
  TFile *file = TFile::Open("root/data/ParticleAnalysis.root");
  if (!file || file->IsZombie())
  {
    std::cerr << "Errore nell'apertura del file ParticleAnalysis.root" << std::endl;
    return;
  }

  // Ottieni l'istogramma dei tipi di particelle
  TH1F *hParticleTypes = (TH1F *)file->Get("hParticleTypes");
  if (!hParticleTypes)
  {
    std::cerr << "Istogramma hParticleTypes non trovato nel file!" << std::endl;
    file->Close();
    return;
  }

  // Numero totale di particelle generate
  double totalEntries = hParticleTypes->GetEntries();
  std::cout << "Numero totale di particelle generate: " << totalEntries << std::endl;

  // Ciclo sui tipi di particelle per verificare le proporzioni
  for (int i = 1; i <= nParticleTypes; ++i)
  {
    double binContent = hParticleTypes->GetBinContent(i);          // Conteggio particelle per questo tipo
    double binError = hParticleTypes->GetBinError(i);              // Errore statistico
    double observedProportion = (binContent / totalEntries) * 100; // Proporzione osservata
    double expectedProportion = expectedProportions[i - 1];        // Proporzione teorica

    // Calcola la differenza tra proporzione osservata e teorica
    double proportionDifference = observedProportion - expectedProportion;

    // Stampa i risultati per il tipo di particella
    std::cout << "Particella tipo " << i - 1 << ":"
              << "\n  Conteggio: " << binContent
              << "\n  Errore statistico: " << binError
              << "\n  Proporzione osservata: " << observedProportion << "%"
              << "\n  Proporzione teorica: " << expectedProportion << "%"
              << "\n  Differenza: " << proportionDifference << "%\n"
              << std::endl;
  }

  // Chiudi il file
  file->Close();
  delete file;

  std::cout << "Verifica delle proporzioni delle specie di particelle completata." << std::endl;
}