// Macro per analizzare gli istogrammi di massa invariante e eseguire le sottrazioni richieste

#include "TFile.h"
#include "TH1F.h"
#include "TF1.h"
#include "TCanvas.h"
#include <iostream>

void analyze_invariant_mass()
{
  // Apro il file ROOT contenente gli istogrammi
  TFile *file = TFile::Open("root/data/ParticleAnalysis.root");
  if (!file || file->IsZombie())
  {
    std::cerr << "Errore nell'apertura del file ParticleAnalysis.root" << std::endl;
    return;
  }

  // Ottengo gli istogrammi necessari dal file ROOT
  TH1F *hInvMassOppositeCharge = (TH1F *)file->Get("hInvMassOppositeCharge");
  TH1F *hInvMassSameCharge = (TH1F *)file->Get("hInvMassSameCharge");
  TH1F *hInvMassPionKaon = (TH1F *)file->Get("hInvMassPionKaon");
  TH1F *hInvMassPionKaonSC = (TH1F *)file->Get("hInvMassPionKaonSC");
  TH1F *hInvMassDecayProducts = (TH1F *)file->Get("hInvMassDecayProducts");

  // Verifico che tutti gli istogrammi siano stati correttamente caricati
  if (!hInvMassOppositeCharge || !hInvMassSameCharge || !hInvMassPionKaon || !hInvMassPionKaonSC || !hInvMassDecayProducts)
  {
    std::cerr << "Errore nel recupero degli istogrammi dal file!" << std::endl;
    file->Close();
    return;
  }

  // Mi assicuro che la somma dei pesi al quadrato sia attivata per calcolare correttamente gli errori
  hInvMassOppositeCharge->Sumw2();
  hInvMassSameCharge->Sumw2();
  hInvMassPionKaon->Sumw2();
  hInvMassPionKaonSC->Sumw2();
  hInvMassDecayProducts->Sumw2();

  // **Eseguo le sottrazioni richieste tra gli istogrammi**

  // 1) Sottrai l'istogramma delle masse invarianti con stessa carica da quello con carica opposta
  // Questo aiuta a eliminare il background simmetrico e mettere in evidenza possibili picchi dovuti a particelle risonanti
  TH1F *hSubtractedAll = (TH1F *)hInvMassOppositeCharge->Clone("hSubtractedAll");
  hSubtractedAll->SetTitle("Invariant Mass (Opposite Charge - Same Charge)");
  hSubtractedAll->GetXaxis()->SetTitle("Invariant Mass (GeV/c^{2})");
  hSubtractedAll->GetYaxis()->SetTitle("Counts");
  hSubtractedAll->Add(hInvMassSameCharge, -1); // Esegue la sottrazione bin per bin

  // 2) Sottrai l'istogramma delle masse invarianti Pion-Kaon con stessa carica da quello con carica opposta
  // Questo isolamento specifico aiuta a evidenziare il picco della K*
  TH1F *hSubtractedPionKaon = (TH1F *)hInvMassPionKaon->Clone("hSubtractedPionKaon");
  hSubtractedPionKaon->SetTitle("Invariant Mass Pion-Kaon (Opposite Charge - Same Charge)");
  hSubtractedPionKaon->GetXaxis()->SetTitle("Invariant Mass (GeV/c^{2})");
  hSubtractedPionKaon->GetYaxis()->SetTitle("Counts");
  hSubtractedPionKaon->Add(hInvMassPionKaonSC, -1); // Esegue la sottrazione bin per bin

  // **Salvo gli istogrammi risultanti per una verifica visiva**

  // Salvo l'istogramma sottratto generale (tutte le coppie di particelle)
  TCanvas *c1 = new TCanvas("cSubtractedAll", "Invariant Mass Subtraction All", 800, 600);
  hSubtractedAll->Draw();
  c1->SaveAs("charts/analyze-invariant-mass/hSubtractedAll.pdf");
  delete c1;

  // Salvo l'istogramma sottratto specifico per coppie Pion-Kaon
  TCanvas *c2 = new TCanvas("cSubtractedPionKaon", "Invariant Mass Subtraction Pion-Kaon", 800, 600);
  hSubtractedPionKaon->Draw();
  c2->SaveAs("charts/analyze-invariant-mass/hSubtractedPionKaon.pdf");
  delete c2;

  // **Confronto con l'istogramma dei decadimenti diretti della K***

  // Salvo l'istogramma delle masse invarianti dei prodotti di decadimento della K*
  TCanvas *c3 = new TCanvas("cDecayProducts", "Invariant Mass Decay Products", 800, 600);
  hInvMassDecayProducts->Draw();
  c3->SaveAs("charts/analyze-invariant-mass/hInvMassDecayProducts.pdf");
  delete c3;

  // **Verifica della presenza di un picco alla massa della K***
  // Eseguo un fit gaussiano sugli istogrammi sottratti per identificare il picco corrispondente alla K*

  // Definisco la funzione gaussiana per il fit, limitata a un range intorno alla massa attesa della K* (~0.892 GeV/c^2)
  TF1 *gausFit = new TF1("gausFit", "gaus", 0.75, 1.05); // La funzione "gaus" ha tre parametri: costante, media, sigma

  // **Fit sull'istogramma hSubtractedAll**

  std::cout << "\nFit dell'istogramma hSubtractedAll con una gaussiana:" << std::endl;
  TCanvas *cFit1 = new TCanvas("cFitSubtractedAll", "Fit Subtracted All", 800, 600);
  hSubtractedAll->Fit("gausFit", "R"); // "R" limita il fit al range definito nella funzione
  hSubtractedAll->Draw();
  cFit1->SaveAs("charts/analyze-invariant-mass/hSubtractedAll_fit.pdf");
  delete cFit1;

  // Ottengo e stampo i risultati del fit per hSubtractedAll
  double chi2 = gausFit->GetChisquare();
  int ndf = gausFit->GetNDF();
  double prob = gausFit->GetProb();
  double mean = gausFit->GetParameter(1);      // Media della gaussiana (posizione del picco)
  double meanError = gausFit->GetParError(1);  // Errore sulla media
  double sigma = gausFit->GetParameter(2);     // Deviazione standard (larghezza del picco)
  double sigmaError = gausFit->GetParError(2); // Errore sulla deviazione standard

  std::cout << "Risultati del fit per hSubtractedAll:" << std::endl;
  std::cout << "Massa (media): " << mean << " ± " << meanError << " GeV/c^2" << std::endl;
  std::cout << "Larghezza (sigma): " << sigma << " ± " << sigmaError << " GeV/c^2" << std::endl;
  std::cout << "Chi2/NDF: " << chi2 << "/" << ndf << " = " << chi2 / ndf << std::endl;
  std::cout << "Probabilità del fit: " << prob << std::endl;

  // **Fit sull'istogramma hSubtractedPionKaon**

  std::cout << "\nFit dell'istogramma hSubtractedPionKaon con una gaussiana:" << std::endl;
  TCanvas *cFit2 = new TCanvas("cFitSubtractedPionKaon", "Fit Subtracted Pion-Kaon", 800, 600);
  hSubtractedPionKaon->Fit("gausFit", "R"); // Riutilizziamo la funzione gaussiana definita prima
  hSubtractedPionKaon->Draw();
  cFit2->SaveAs("charts/analyze-invariant-mass/hSubtractedPionKaon_fit.pdf");
  delete cFit2;

  // Ottengo e stampo i risultati del fit per hSubtractedPionKaon
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

  // **Fit sull'istogramma dei decadimenti diretti della K***

  std::cout << "\nConfronto con l'istogramma hInvMassDecayProducts:" << std::endl;
  TCanvas *cFit3 = new TCanvas("cFitDecayProducts", "Fit Decay Products", 800, 600);
  hInvMassDecayProducts->Fit("gausFit", "R"); // Fit della gaussiana sui dati dei decadimenti reali
  hInvMassDecayProducts->Draw();
  cFit3->SaveAs("charts/analyze-invariant-mass/hInvMassDecayProducts_fit.pdf");
  delete cFit3;

  // Ottengo e stampo i risultati del fit per hInvMassDecayProducts
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

  // **Chiudo il file ROOT e libero la memoria**

  file->Close();
  delete file;
  delete gausFit;

  std::cout << "\nAnalisi degli istogrammi di massa invariante completata." << std::endl;
  std::cout << "I grafici sono stati salvati nella cartella 'charts'." << std::endl;
}