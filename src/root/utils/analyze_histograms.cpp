// analyze_histograms.C
// Macro per analizzare e verificare il numero di ingressi degli istogrammi salvati

#include "TFile.h"
#include "TH1F.h"
#include "TCanvas.h"
#include <iostream>

void analyze_histograms()
{
  // Viene aperto il file ROOT contenente gli istogrammi
  TFile *file = TFile::Open("root/data/ParticleAnalysis.root");
  if (!file || file->IsZombie()) // Controlla se il file è stato aperto correttamente
  {
    std::cerr << "Errore nell'apertura del file ParticleAnalysis.root" << std::endl;
    return;
  }

  // Array con i nomi degli istogrammi da analizzare
  const char *histNames[] = {
      "hParticleTypes",         // Distribuzione dei tipi di particelle
      "hAzimuthalAngle",        // Distribuzione degli angoli azimutali (phi)
      "hPolarAngle",            // Distribuzione degli angoli polari (theta)
      "hMomentum",              // Distribuzione del modulo dell'impulso
      "hTransverseMomentum",    // Distribuzione dell'impulso trasverso
      "hEnergy",                // Distribuzione dell'energia
      "hInvariantMass",         // Masse invarianti per tutte le coppie
      "hInvMassOppositeCharge", // Masse invarianti per coppie con carica opposta
      "hInvMassSameCharge",     // Masse invarianti per coppie con stessa carica
      "hInvMassPionKaon",       // Masse invarianti per coppie Pion-Kaon (carica opposta)
      "hInvMassPionKaonSC",     // Masse invarianti per coppie Pion-Kaon (stessa carica)
      "hInvMassDecayProducts"   // Masse invarianti dei prodotti di decadimento della K*
  };

  const int nHists = sizeof(histNames) / sizeof(histNames[0]); // Numero di istogrammi da analizzare

  // Ciclo su ciascun istogramma per analizzarlo
  for (int i = 0; i < nHists; ++i)
  {
    // Ottengo l'istogramma dal file ROOT utilizzando il nome
    TH1F *hist = (TH1F *)file->Get(histNames[i]);
    if (!hist) // Controlla che l'istogramma sia stato trovato
    {
      std::cerr << "Istogramma " << histNames[i] << " non trovato nel file!" << std::endl;
      continue; // Passo all'istogramma successivo se non è presente
    }

    // Ottengo il numero totale di ingressi (entries) nell'istogramma
    int entries = hist->GetEntries();
    std::cout << "Istogramma: " << histNames[i] << " - Numero di ingressi: " << entries << std::endl;

    // Verifica visiva: l'istogramma viene disegnato e il risultato salvato come file PDF
    TCanvas *c = new TCanvas(histNames[i], histNames[i], 800, 600);  // Crea un canvas con il nome dell'istogramma
    hist->Draw();                                                    // Disegna l'istogramma sul canvas
    c->SaveAs(TString::Format("charts/analyze-histograms/%s_check.pdf", histNames[i])); // Salva il canvas come file PDF nella cartella "charts"
    delete c;                                                        // Libera la memoria associata al canvas
  }

  // Chiudo il file ROOT dopo aver analizzato tutti gli istogrammi
  file->Close();
  delete file;

  // Messaggio di completamento dell'analisi
  std::cout << "Analisi completata. Controlla la cartella 'charts' per i file PDF generati." << std::endl;
}