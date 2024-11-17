// Macro per verificare se le distribuzioni angolari (azimutale e polare)
// sono consistenti con una distribuzione uniforme.

#include "TFile.h"
#include "TH1F.h"
#include "TF1.h"
#include "TCanvas.h"
#include <iostream>

void check_angular_distributions()
{
  // Apre il file ROOT contenente gli istogrammi.
  TFile *file = TFile::Open("root/data/ParticleAnalysis.root");
  if (!file || file->IsZombie()) // Controlla se il file è stato aperto correttamente.
  {
    std::cerr << "Errore nell'apertura del file ParticleAnalysis.root" << std::endl;
    return;
  }

  // Ottiene gli istogrammi delle distribuzioni angolari:
  // - hAzimuthalAngle: distribuzione dell'angolo azimutale (phi, 0 a 2π).
  // - hPolarAngle: distribuzione dell'angolo polare (theta, 0 a π).
  TH1F *hAzimuthalAngle = (TH1F *)file->Get("hAzimuthalAngle");
  TH1F *hPolarAngle = (TH1F *)file->Get("hPolarAngle");

  if (!hAzimuthalAngle || !hPolarAngle) // Verifica che entrambi gli istogrammi siano stati trovati.
  {
    std::cerr << "Istogrammi hAzimuthalAngle o hPolarAngle non trovati!" << std::endl;
    file->Close();
    return;
  }

  // Definizione della funzione uniforme per il fit:
  // - La funzione è costante, rappresentando una distribuzione uniforme.
  // - Il valore iniziale è calcolato come: totale degli ingressi diviso il numero di bin.
  TF1 *uniformFit = new TF1("uniformFit", "[0]", 0, 2 * TMath::Pi());
  uniformFit->SetParameter(0, hAzimuthalAngle->GetEntries() / hAzimuthalAngle->GetNbinsX());
  uniformFit->SetLineColor(kRed); // Colore rosso per il fit.
  uniformFit->SetLineWidth(2);

  // Fit della distribuzione azimutale (phi).
  std::cout << "Fit della distribuzione azimutale (hAzimuthalAngle):" << std::endl;
  TCanvas *c1 = new TCanvas("cAzimuthalAngle", "Fit Azimuthal Angle", 800, 600);
  hAzimuthalAngle->Fit("uniformFit", "Q"); // Esegue il fit in modalità silenziosa ("Q").
  hAzimuthalAngle->Draw("E");              // Disegna l'istogramma con gli errori statistici.

  // Ottiene i risultati del fit per la distribuzione azimutale:
  // - Chi2: bontà del fit (minore è meglio).
  // - NDF: numero di gradi di libertà.
  // - Probabilità: probabilità che i dati siano consistenti con il modello.
  double chi2 = uniformFit->GetChisquare();
  int ndf = uniformFit->GetNDF();
  double prob = uniformFit->GetProb();
  double param = uniformFit->GetParameter(0);
  double paramError = uniformFit->GetParError(0);

  // Stampa dei risultati per la distribuzione azimutale.
  std::cout << "Parametro del fit: " << param << " ± " << paramError << std::endl;
  std::cout << "Chi2/NDF: " << chi2 << "/" << ndf << " = " << chi2 / ndf << std::endl;
  std::cout << "Probabilità del fit: " << prob << std::endl;

  // Salva il fit della distribuzione azimutale come file PDF.
  c1->SaveAs("charts/check-angular-distributions/hAzimuthalAngle_fit.pdf");
  delete c1;

  // Modifica il range della funzione uniforme per adattarla alla distribuzione polare (theta, 0 a π).
  uniformFit->SetRange(0, TMath::Pi());
  uniformFit->SetParameter(0, hPolarAngle->GetEntries() / hPolarAngle->GetNbinsX());
  uniformFit->SetLineColor(kRed); // Imposta nuovamente il colore rosso.
  uniformFit->SetLineWidth(2);

  // Fit della distribuzione polare (theta).
  std::cout << "\nFit della distribuzione polare (hPolarAngle):" << std::endl;
  TCanvas *c2 = new TCanvas("cPolarAngle", "Fit Polar Angle", 800, 600);
  hPolarAngle->Fit("uniformFit", "Q"); // Fit silenzioso.
  hPolarAngle->Draw("E");              // Disegna l'istogramma con gli errori statistici.

  // Ottiene i risultati del fit per la distribuzione polare.
  chi2 = uniformFit->GetChisquare();
  ndf = uniformFit->GetNDF();
  prob = uniformFit->GetProb();
  param = uniformFit->GetParameter(0);
  paramError = uniformFit->GetParError(0);

  // Stampa dei risultati per la distribuzione polare.
  std::cout << "Parametro del fit: " << param << " ± " << paramError << std::endl;
  std::cout << "Chi2/NDF: " << chi2 << "/" << ndf << " = " << chi2 / ndf << std::endl;
  std::cout << "Probabilità del fit: " << prob << std::endl;

  // Salva il fit della distribuzione polare come file PDF.
  c2->SaveAs("charts/check-angular-distributions/hPolarAngle_fit.pdf");
  delete c2;

  // Chiude il file ROOT e libera la memoria.
  file->Close();
  delete file;
  delete uniformFit;

  // Messaggio di completamento dell'analisi.
  std::cout << "Analisi delle distribuzioni angolari completata." << std::endl;
}