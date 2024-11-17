// Macro per verificare la distribuzione delle specie di particelle
// confrontando le proporzioni osservate con quelle teoriche.

#include "TFile.h"
#include "TH1F.h"
#include <iostream>

void verify_particle_distribution()
{
  // Proporzioni teoriche attese per ogni tipo di particella (in percentuale).
  // Questi valori sono definiti dal modello di generazione usato nella simulazione.
  const double expectedProportions[] = {
      40.0, // Pion+ (40% del totale)
      40.0, // Pion- (40% del totale)
      5.0,  // Kaon+ (5% del totale)
      5.0,  // Kaon- (5% del totale)
      4.5,  // Proton+ (4.5% del totale)
      4.5,  // Proton- (4.5% del totale)
      1.0   // K* (1% del totale)
  };

  // Calcola il numero totale di tipi di particelle.
  const int nParticleTypes = sizeof(expectedProportions) / sizeof(expectedProportions[0]);

  // Apre il file ROOT contenente i dati della simulazione.
  TFile *file = TFile::Open("root/data/ParticleAnalysis.root");
  if (!file || file->IsZombie()) // Controlla se il file è aperto correttamente.
  {
    std::cerr << "Errore nell'apertura del file ParticleAnalysis.root" << std::endl;
    return;
  }

  // Ottieni l'istogramma `hParticleTypes` che contiene il conteggio delle particelle generate per ogni tipo.
  TH1F *hParticleTypes = (TH1F *)file->Get("hParticleTypes");
  if (!hParticleTypes) // Controlla se l'istogramma esiste nel file ROOT.
  {
    std::cerr << "Istogramma hParticleTypes non trovato nel file!" << std::endl;
    file->Close();
    return;
  }

  // Ottieni il numero totale di particelle generate.
  double totalEntries = hParticleTypes->GetEntries();
  std::cout << "Numero totale di particelle generate: " << totalEntries << std::endl;

  // Loop attraverso tutti i tipi di particelle presenti nell'istogramma.
  for (int i = 1; i <= nParticleTypes; ++i) // Gli indici dei bin iniziano da 1.
  {
    // Conteggio delle particelle per il tipo corrispondente al bin corrente.
    double binContent = hParticleTypes->GetBinContent(i);

    // Errore statistico associato al conteggio (radice quadrata del conteggio in generale).
    double binError = hParticleTypes->GetBinError(i);

    // Calcola la proporzione osservata come percentuale rispetto al totale delle particelle.
    double observedProportion = (binContent / totalEntries) * 100;

    // Proporzione teorica attesa per il tipo di particella corrente.
    double expectedProportion = expectedProportions[i - 1];

    // Differenza tra la proporzione osservata e quella teorica.
    double proportionDifference = observedProportion - expectedProportion;

    // Stampa i risultati per il tipo di particella corrente.
    std::cout << "Particella tipo " << i - 1 << ":" // Indice del tipo di particella (0-based).
              << "\n  Conteggio: " << binContent
              << "\n  Errore statistico: " << binError
              << "\n  Proporzione osservata: " << observedProportion << "%"
              << "\n  Proporzione teorica: " << expectedProportion << "%"
              << "\n  Differenza: " << proportionDifference << "%\n"
              << std::endl;
  }

  // Chiude il file ROOT dopo aver completato l'analisi.
  file->Close();
  delete file;

  // Messaggio di completamento dell'analisi.
  std::cout << "Verifica delle proporzioni delle specie di particelle completata." << std::endl;
}