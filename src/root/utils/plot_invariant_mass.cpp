// Macro per visualizzare le distribuzioni di massa invariante delle K* vere,
// la massa invariante ottenuta dalla differenza fra combinazioni di carica discorde e concorde,
// e la massa invariante ottenuta dalla differenza fra combinazioni πK di carica discorde e concorde.
// Il tutto su un'unica canvas divisa in 3 pad, con fit sovrapposti e parametri stampati nella box della statistica.
// Sono stati aggiunti titoli agli assi.

#include "TFile.h"
#include "TH1F.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TStyle.h"
#include <iostream>

void plot_invariant_mass()
{
  // Apri il file ROOT contenente gli istogrammi
  TFile *file = TFile::Open("root/data/ParticleAnalysis.root");
  if (!file || file->IsZombie())
  {
    std::cerr << "Errore nell'apertura del file ParticleAnalysis.root" << std::endl;
    return;
  }

  // Ottieni gli istogrammi necessari dal file ROOT
  TH1F *hInvMassOppositeCharge = (TH1F *)file->Get("hInvMassOppositeCharge");
  TH1F *hInvMassSameCharge = (TH1F *)file->Get("hInvMassSameCharge");
  TH1F *hInvMassPionKaon = (TH1F *)file->Get("hInvMassPionKaon");
  TH1F *hInvMassPionKaonSC = (TH1F *)file->Get("hInvMassPionKaonSC");
  TH1F *hInvMassDecayProducts = (TH1F *)file->Get("hInvMassDecayProducts");

  // Verifica che tutti gli istogrammi siano stati correttamente caricati
  if (!hInvMassOppositeCharge || !hInvMassSameCharge || !hInvMassPionKaon || !hInvMassPionKaonSC || !hInvMassDecayProducts)
  {
    std::cerr << "Errore nel recupero degli istogrammi dal file!" << std::endl;
    file->Close();
    return;
  }

  // Attiva la somma dei pesi al quadrato per calcolare correttamente gli errori
  hInvMassOppositeCharge->Sumw2();
  hInvMassSameCharge->Sumw2();
  hInvMassPionKaon->Sumw2();
  hInvMassPionKaonSC->Sumw2();
  hInvMassDecayProducts->Sumw2();

  // **Esegui le sottrazioni richieste tra gli istogrammi**

  // 1) Sottrai l'istogramma delle masse invarianti con stessa carica da quello con carica opposta
  TH1F *hSubtractedAll = (TH1F *)hInvMassOppositeCharge->Clone("hSubtractedAll");
  hSubtractedAll->SetTitle("Invariant Mass (Opposite Charge - Same Charge)");
  hSubtractedAll->GetXaxis()->SetTitle("Invariant Mass (GeV/c^{2})");
  hSubtractedAll->GetYaxis()->SetTitle("Counts");
  hSubtractedAll->Add(hInvMassSameCharge, -1); // Esegue la sottrazione bin per bin

  // 2) Sottrai l'istogramma delle masse invarianti Pion-Kaon con stessa carica da quello con carica opposta
  TH1F *hSubtractedPionKaon = (TH1F *)hInvMassPionKaon->Clone("hSubtractedPionKaon");
  hSubtractedPionKaon->SetTitle("Invariant Mass Pion-Kaon (Opposite Charge - Same Charge)");
  hSubtractedPionKaon->GetXaxis()->SetTitle("Invariant Mass (GeV/c^{2})");
  hSubtractedPionKaon->GetYaxis()->SetTitle("Counts");
  hSubtractedPionKaon->Add(hInvMassPionKaonSC, -1); // Esegue la sottrazione bin per bin

  // **Imposta lo stile per visualizzare i parametri del fit nella box della statistica**
  gStyle->SetOptFit(1111); // Mostra tutti i parametri del fit

  // Crea una canvas divisa in 3 pad
  TCanvas *c = new TCanvas("cInvariantMass", "Invariant Mass Distributions", 1200, 900);
  c->Divide(1, 3); // Divide la canvas in 1x3 pad

  // **Definisci la funzione gaussiana per i fit**
  TF1 *gausFit = new TF1("gausFit", "gaus", 0.75, 1.05); // Range intorno alla massa del K*

  // **1) Istogramma delle masse invarianti delle K* vere**
  c->cd(1); // Seleziona il primo pad
  hInvMassDecayProducts->SetTitle("Invariant Mass of True K^{*} Decay Products");
  hInvMassDecayProducts->GetXaxis()->SetTitle("Invariant Mass (GeV/c^{2})");
  hInvMassDecayProducts->GetYaxis()->SetTitle("Counts");
  hInvMassDecayProducts->SetLineColor(kBlue);
  hInvMassDecayProducts->Draw("E");

  // Esegui il fit gaussiano sull'istogramma
  hInvMassDecayProducts->Fit("gausFit", "R"); // "R" limita il fit al range della funzione

  // **2) Istogramma della massa invariante ottenuta dalla differenza fra combinazioni di carica discorde e concorde**
  c->cd(2); // Seleziona il secondo pad
  hSubtractedAll->SetTitle("Invariant Mass (Opposite - Same Charge Combinations)");
  hSubtractedAll->GetXaxis()->SetTitle("Invariant Mass (GeV/c^{2})");
  hSubtractedAll->GetYaxis()->SetTitle("Counts");
  hSubtractedAll->SetLineColor(kBlue);
  hSubtractedAll->Draw("E");

  // Esegui il fit gaussiano sull'istogramma
  hSubtractedAll->Fit("gausFit", "R");

  // **3) Istogramma della massa invariante ottenuta dalla differenza fra combinazioni πK di carica discorde e concorde**
  c->cd(3); // Seleziona il terzo pad
  hSubtractedPionKaon->SetTitle("Invariant Mass #pi K (Opposite - Same Charge)");
  hSubtractedPionKaon->GetXaxis()->SetTitle("Invariant Mass (GeV/c^{2})");
  hSubtractedPionKaon->GetYaxis()->SetTitle("Counts");
  hSubtractedPionKaon->SetLineColor(kBlue);
  hSubtractedPionKaon->Draw("E");

  // Esegui il fit gaussiano sull'istogramma
  hSubtractedPionKaon->Fit("gausFit", "R");

  // **Salva la canvas come file PDF**
  c->SaveAs("charts/plot-invariant-mass/invariant_mass_distributions.pdf");

  // **Pulizia della memoria**
  delete gausFit;
  delete c;

  // Chiudi il file ROOT
  file->Close();
  delete file;

  // Messaggio di completamento
  std::cout << "Plot delle masse invarianti completato. Il grafico è stato salvato in 'charts/plot-invariant-mass/invariant_mass_distributions.pdf'." << std::endl;
}