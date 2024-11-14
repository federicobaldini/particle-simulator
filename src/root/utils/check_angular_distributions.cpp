// check_angular_distributions.C
// Macro per verificare se le distribuzioni angolari sono consistenti con una distribuzione uniforme

#include "TFile.h"
#include "TH1F.h"
#include "TF1.h"
#include "TCanvas.h"
#include <iostream>

void check_angular_distributions()
{
  // Apri il file ROOT contenente gli istogrammi
  TFile *file = TFile::Open("/root/data/ParticleAnalysis.root");
  if (!file || file->IsZombie())
  {
    std::cerr << "Errore nell'apertura del file ParticleAnalysis.root" << std::endl;
    return;
  }

  // Ottieni gli istogrammi delle distribuzioni angolari
  TH1F *hAzimuthalAngle = (TH1F *)file->Get("hAzimuthalAngle");
  TH1F *hPolarAngle = (TH1F *)file->Get("hPolarAngle");

  if (!hAzimuthalAngle || !hPolarAngle)
  {
    std::cerr << "Istogrammi hAzimuthalAngle o hPolarAngle non trovati!" << std::endl;
    file->Close();
    return;
  }

  // Definisci una funzione uniforme per il fit
  TF1 *uniformFit = new TF1("uniformFit", "[0]", 0, 2 * TMath::Pi());                        // Funzione costante per la distribuzione uniforme
  uniformFit->SetParameter(0, hAzimuthalAngle->GetEntries() / hAzimuthalAngle->GetNbinsX()); // Valore iniziale per il fit
  uniformFit->SetLineColor(kRed);                                                            // Linea di fit in rosso
  uniformFit->SetLineWidth(2);

  // Esegui il fit sulla distribuzione azimutale
  std::cout << "Fit della distribuzione azimutale (hAzimuthalAngle):" << std::endl;
  TCanvas *c1 = new TCanvas("cAzimuthalAngle", "Fit Azimuthal Angle", 800, 600);
  hAzimuthalAngle->Fit("uniformFit", "Q"); // "Q" per eseguire il fit in modalità silenziosa
  hAzimuthalAngle->Draw("E");              // Disegna con errori sui dati

  // Ottieni e stampa i risultati del fit per la distribuzione azimutale
  double chi2 = uniformFit->GetChisquare();
  int ndf = uniformFit->GetNDF();
  double prob = uniformFit->GetProb();
  double param = uniformFit->GetParameter(0);
  double paramError = uniformFit->GetParError(0);

  std::cout << "Parametro del fit: " << param << " ± " << paramError << std::endl;
  std::cout << "Chi2/NDF: " << chi2 << "/" << ndf << " = " << chi2 / ndf << std::endl;
  std::cout << "Probabilità del fit: " << prob << std::endl;

  c1->SaveAs("charts/hAzimuthalAngle_fit.pdf"); // Salva il risultato del fit come PDF
  delete c1;

  // Modifica il range della funzione di fit per la distribuzione polare (0 a π)
  uniformFit->SetRange(0, TMath::Pi());
  uniformFit->SetParameter(0, hPolarAngle->GetEntries() / hPolarAngle->GetNbinsX()); // Aggiorna il valore iniziale
  uniformFit->SetLineColor(kRed);                                                    // Linea di fit in rosso
  uniformFit->SetLineWidth(2);

  // Esegui il fit sulla distribuzione polare
  std::cout << "\nFit della distribuzione polare (hPolarAngle):" << std::endl;
  TCanvas *c2 = new TCanvas("cPolarAngle", "Fit Polar Angle", 800, 600);
  hPolarAngle->Fit("uniformFit", "Q"); // Fit silenzioso
  hPolarAngle->Draw("E");

  // Ottieni e stampa i risultati del fit per la distribuzione polare
  chi2 = uniformFit->GetChisquare();
  ndf = uniformFit->GetNDF();
  prob = uniformFit->GetProb();
  param = uniformFit->GetParameter(0);
  paramError = uniformFit->GetParError(0);

  std::cout << "Parametro del fit: " << param << " ± " << paramError << std::endl;
  std::cout << "Chi2/NDF: " << chi2 << "/" << ndf << " = " << chi2 / ndf << std::endl;
  std::cout << "Probabilità del fit: " << prob << std::endl;

  c2->SaveAs("charts/hPolarAngle_fit.pdf"); // Salva il risultato del fit come PDF
  delete c2;

  // Chiudi il file ROOT
  file->Close();
  delete file;
  delete uniformFit;

  std::cout << "Analisi delle distribuzioni angolari completata." << std::endl;
}