// check_momentum_distribution.C
// Macro per verificare se la distribuzione del modulo dell'impulso è esponenziale e consistente con la media attesa

#include "TFile.h"
#include "TH1F.h"
#include "TF1.h"
#include "TCanvas.h"
#include <iostream>

void check_momentum_distribution()
{
  // Apri il file ROOT contenente gli istogrammi
  TFile *file = TFile::Open("root/data/ParticleAnalysis.root");
  if (!file || file->IsZombie())
  {
    std::cerr << "Errore nell'apertura del file ParticleAnalysis.root" << std::endl;
    return;
  }

  // Ottieni l'istogramma del modulo dell'impulso
  TH1F *hMomentum = (TH1F *)file->Get("hMomentum");
  if (!hMomentum)
  {
    std::cerr << "Istogramma hMomentum non trovato nel file!" << std::endl;
    file->Close();
    return;
  }

  // Definisci la funzione esponenziale per il fit
  TF1 *expFit = new TF1("expFit", "[0]*exp(-x/[1])", 0, 5); // [0] è la normalizzazione, [1] è il valore atteso
  expFit->SetParameter(1, 1.0);                             // Imposta un valore iniziale per la media (1 GeV)
  expFit->SetLineColor(kRed);                               // Linea di fit in rosso
  expFit->SetLineWidth(2);

  // Esegui il fit della distribuzione del modulo dell'impulso
  std::cout << "Fit della distribuzione del modulo dell'impulso (hMomentum):" << std::endl;
  TCanvas *c1 = new TCanvas("cMomentum", "Fit Momentum", 800, 600);
  hMomentum->Fit("expFit", "Q"); // Fit in modalità silenziosa
  hMomentum->Draw("E");          // Disegna con errori sui dati

  // Ottieni e stampa i risultati del fit
  double chi2 = expFit->GetChisquare();
  int ndf = expFit->GetNDF();
  double prob = expFit->GetProb();
  double param0 = expFit->GetParameter(0);
  double param0Error = expFit->GetParError(0);
  double param1 = expFit->GetParameter(1); // Media della distribuzione esponenziale
  double param1Error = expFit->GetParError(1);

  std::cout << "Parametro del fit [0] (Normalizzazione): " << param0 << " ± " << param0Error << std::endl;
  std::cout << "Parametro del fit [1] (Media): " << param1 << " ± " << param1Error << std::endl;
  std::cout << "Chi2/NDF: " << chi2 << "/" << ndf << " = " << chi2 / ndf << std::endl;
  std::cout << "Probabilità del fit: " << prob << std::endl;

  // Verifica della consistenza della media con il valore atteso
  double expectedMean = 1.0;
  if (std::abs(param1 - expectedMean) <= param1Error)
  {
    std::cout << "La media ottenuta è consistente con la media attesa (" << expectedMean << " GeV) entro gli errori." << std::endl;
  }
  else
  {
    std::cout << "La media ottenuta NON è consistente con la media attesa (" << expectedMean << " GeV)." << std::endl;
  }

  // Salva il risultato del fit come PDF per verifica visiva
  c1->SaveAs("../../charts/hMomentum_fit.pdf");
  delete c1;

  // Chiudi il file ROOT
  file->Close();
  delete file;
  delete expFit;

  std::cout << "Verifica della distribuzione del modulo dell'impulso completata." << std::endl;
}