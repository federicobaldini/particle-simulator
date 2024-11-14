// analyze_invariant_mass.C
// Macro per analizzare gli istogrammi di massa invariante e eseguire le sottrazioni richieste

#include "TFile.h"
#include "TH1F.h"
#include "TF1.h"
#include "TCanvas.h"
#include <iostream>

void analyze_invariant_mass()
{
  // Apri il file ROOT contenente gli istogrammi
  TFile *file = TFile::Open("root/data/ParticleAnalysis.root");
  if (!file || file->IsZombie())
  {
    std::cerr << "Errore nell'apertura del file ParticleAnalysis.root" << std::endl;
    return;
  }

  // Ottieni gli istogrammi necessari
  TH1F *hInvMassOppositeCharge = (TH1F *)file->Get("hInvMassOppositeCharge");
  TH1F *hInvMassSameCharge = (TH1F *)file->Get("hInvMassSameCharge");
  TH1F *hInvMassPionKaon = (TH1F *)file->Get("hInvMassPionKaon");
  TH1F *hInvMassPionKaonSC = (TH1F *)file->Get("hInvMassPionKaonSC");
  TH1F *hInvMassDecayProducts = (TH1F *)file->Get("hInvMassDecayProducts");

  if (!hInvMassOppositeCharge || !hInvMassSameCharge || !hInvMassPionKaon || !hInvMassPionKaonSC || !hInvMassDecayProducts)
  {
    std::cerr << "Errore nel recupero degli istogrammi dal file!" << std::endl;
    file->Close();
    return;
  }

  // Verifica che Sumw2() sia stato chiamato (dovrebbe essere già fatto nel tuo codice)
  // Se non lo fosse, lo chiamiamo qui per sicurezza
  hInvMassOppositeCharge->Sumw2();
  hInvMassSameCharge->Sumw2();
  hInvMassPionKaon->Sumw2();
  hInvMassPionKaonSC->Sumw2();
  hInvMassDecayProducts->Sumw2();

  // Esegui le sottrazioni richieste
  // 1) - 2)
  TH1F *hSubtractedAll = (TH1F *)hInvMassOppositeCharge->Clone("hSubtractedAll");
  hSubtractedAll->SetTitle("Invariant Mass (Opposite Charge - Same Charge)");
  hSubtractedAll->GetXaxis()->SetTitle("Invariant Mass (GeV/c^{2})");
  hSubtractedAll->GetYaxis()->SetTitle("Counts");
  hSubtractedAll->Add(hInvMassSameCharge, -1);

  // 3) - 4)
  TH1F *hSubtractedPionKaon = (TH1F *)hInvMassPionKaon->Clone("hSubtractedPionKaon");
  hSubtractedPionKaon->SetTitle("Invariant Mass Pion-Kaon (Opposite Charge - Same Charge)");
  hSubtractedPionKaon->GetXaxis()->SetTitle("Invariant Mass (GeV/c^{2})");
  hSubtractedPionKaon->GetYaxis()->SetTitle("Counts");
  hSubtractedPionKaon->Add(hInvMassPionKaonSC, -1);

  // Salva gli istogrammi risultanti per verifica visiva
  TCanvas *c1 = new TCanvas("cSubtractedAll", "Invariant Mass Subtraction All", 800, 600);
  hSubtractedAll->Draw();
  c1->SaveAs("charts/hSubtractedAll.pdf");
  delete c1;

  TCanvas *c2 = new TCanvas("cSubtractedPionKaon", "Invariant Mass Subtraction Pion-Kaon", 800, 600);
  hSubtractedPionKaon->Draw();
  c2->SaveAs("charts/hSubtractedPionKaon.pdf");
  delete c2;

  // Confronto con l'istogramma dei decadimenti della K*
  TCanvas *c3 = new TCanvas("cDecayProducts", "Invariant Mass Decay Products", 800, 600);
  hInvMassDecayProducts->Draw();
  c3->SaveAs("charts/hInvMassDecayProducts.pdf");
  delete c3;

  // Verifica se c'è un picco in corrispondenza della massa della K*
  // Fit degli istogrammi risultanti con una funzione gaussiana

  // Definisci la funzione gaussiana
  TF1 *gausFit = new TF1("gausFit", "gaus", 0.75, 1.05); // Range intorno alla massa della K*

  // Fit sull'istogramma hSubtractedAll
  std::cout << "\nFit dell'istogramma hSubtractedAll con una gaussiana:" << std::endl;
  TCanvas *cFit1 = new TCanvas("cFitSubtractedAll", "Fit Subtracted All", 800, 600);
  hSubtractedAll->Fit("gausFit", "R"); // "R" per limitare il fit al range della funzione
  hSubtractedAll->Draw();
  cFit1->SaveAs("charts/hSubtractedAll_fit.pdf");
  delete cFit1;

  // Ottieni e stampa i risultati del fit
  double chi2 = gausFit->GetChisquare();
  int ndf = gausFit->GetNDF();
  double prob = gausFit->GetProb();
  double mean = gausFit->GetParameter(1);
  double meanError = gausFit->GetParError(1);
  double sigma = gausFit->GetParameter(2);
  double sigmaError = gausFit->GetParError(2);

  std::cout << "Risultati del fit per hSubtractedAll:" << std::endl;
  std::cout << "Massa (media): " << mean << " ± " << meanError << " GeV/c^2" << std::endl;
  std::cout << "Larghezza (sigma): " << sigma << " ± " << sigmaError << " GeV/c^2" << std::endl;
  std::cout << "Chi2/NDF: " << chi2 << "/" << ndf << " = " << chi2 / ndf << std::endl;
  std::cout << "Probabilità del fit: " << prob << std::endl;

  // Fit sull'istogramma hSubtractedPionKaon
  std::cout << "\nFit dell'istogramma hSubtractedPionKaon con una gaussiana:" << std::endl;
  TCanvas *cFit2 = new TCanvas("cFitSubtractedPionKaon", "Fit Subtracted Pion-Kaon", 800, 600);
  hSubtractedPionKaon->Fit("gausFit", "R"); // Riutilizziamo la funzione gaussiana
  hSubtractedPionKaon->Draw();
  cFit2->SaveAs("charts/hSubtractedPionKaon_fit.pdf");
  delete cFit2;

  // Ottieni e stampa i risultati del fit
  chi2 = gausFit->GetChisquare();
  ndf = gausFit->GetNDF();
  prob = gausFit->GetProb();
  mean = gausFit->GetParameter(1);
  meanError = gausFit->GetParError(1);
  sigma = gausFit->GetParameter(2);
  sigmaError = gausFit->GetParError(2);

  std::cout << "Risultati del fit per hSubtractedPionKaon:" << std::endl;
  std::cout << "Massa (media): " << mean << " ± " << meanError << " GeV/c^2" << std::endl;
  std::cout << "Larghezza (sigma): " << sigma << " ± " << sigmaError << " GeV/c^2" << std::endl;
  std::cout << "Chi2/NDF: " << chi2 << "/" << ndf << " = " << chi2 / ndf << std::endl;
  std::cout << "Probabilità del fit: " << prob << std::endl;

  // Confronto con l'istogramma dei decadimenti della K*
  std::cout << "\nConfronto con l'istogramma hInvMassDecayProducts:" << std::endl;
  TCanvas *cFit3 = new TCanvas("cFitDecayProducts", "Fit Decay Products", 800, 600);
  hInvMassDecayProducts->Fit("gausFit", "R"); // Fit della gaussiana sui decadimenti reali
  hInvMassDecayProducts->Draw();
  cFit3->SaveAs("charts/hInvMassDecayProducts_fit.pdf");
  delete cFit3;

  // Ottieni e stampa i risultati del fit
  chi2 = gausFit->GetChisquare();
  ndf = gausFit->GetNDF();
  prob = gausFit->GetProb();
  mean = gausFit->GetParameter(1);
  meanError = gausFit->GetParError(1);
  sigma = gausFit->GetParameter(2);
  sigmaError = gausFit->GetParError(2);

  std::cout << "Risultati del fit per hInvMassDecayProducts:" << std::endl;
  std::cout << "Massa (media): " << mean << " ± " << meanError << " GeV/c^2" << std::endl;
  std::cout << "Larghezza (sigma): " << sigma << " ± " << sigmaError << " GeV/c^2" << std::endl;
  std::cout << "Chi2/NDF: " << chi2 << "/" << ndf << " = " << chi2 / ndf << std::endl;
  std::cout << "Probabilità del fit: " << prob << std::endl;

  // Chiudi il file ROOT
  file->Close();
  delete file;
  delete gausFit;

  std::cout << "\nAnalisi degli istogrammi di massa invariante completata." << std::endl;
  std::cout << "I grafici sono stati salvati nella cartella 'charts'." << std::endl;
}