// analyze_histograms.C
// Macro per analizzare e verificare il numero di ingressi degli istogrammi salvati

#include "TFile.h"
#include "TH1F.h"
#include "TCanvas.h"
#include <iostream>

void analyze_histograms()
{
  // Apri il file ROOT contenente gli istogrammi
  TFile *file = TFile::Open("root/data/ParticleAnalysis.root");
  if (!file || file->IsZombie())
  {
    std::cerr << "Errore nell'apertura del file ParticleAnalysis.root" << std::endl;
    return;
  }

  // Definisci un array con i nomi degli istogrammi da analizzare
  const char *histNames[] = {
      "hParticleTypes",
      "hAzimuthalAngle",
      "hPolarAngle",
      "hMomentum",
      "hTransverseMomentum",
      "hEnergy",
      "hInvariantMass",
      "hInvMassOppositeCharge",
      "hInvMassSameCharge",
      "hInvMassPionKaon",
      "hInvMassPionKaonSC",
      "hInvMassDecayProducts"};

  const int nHists = sizeof(histNames) / sizeof(histNames[0]); // Numero di istogrammi

  // Cicla su ciascun istogramma e controlla il numero di ingressi
  for (int i = 0; i < nHists; ++i)
  {
    // Ottieni l'istogramma dal file
    TH1F *hist = (TH1F *)file->Get(histNames[i]);
    if (!hist)
    {
      std::cerr << "Istogramma " << histNames[i] << " non trovato nel file!" << std::endl;
      continue;
    }

    // Ottieni il numero di ingressi per l'istogramma
    int entries = hist->GetEntries();
    std::cout << "Istogramma: " << histNames[i] << " - Numero di ingressi: " << entries << std::endl;

    // Verifica visiva degli istogrammi
    TCanvas *c = new TCanvas(histNames[i], histNames[i], 800, 600);
    hist->Draw();
    c->SaveAs(TString::Format("charts/%s_check.pdf", histNames[i])); // Salva l'istogramma come PDF
    delete c;
  }

  // Chiudi il file
  file->Close();
  delete file;

  std::cout << "Analisi completata. Controlla la cartella 'charts' per i file PDF generati." << std::endl;
}