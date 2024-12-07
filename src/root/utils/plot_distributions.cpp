// Macro per visualizzare le distribuzioni di abbondanza di particelle, impulso,
// angolo polare e angolo azimutale su un'unica canvas divisa in 4 pad, con fit sovrapposti
// e parametri stampati nella box della statistica. Sono stati aggiunti titoli agli assi.

#include "TFile.h"
#include "TH1F.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TStyle.h"
#include <iostream>

void plot_distributions()
{
  // Apro il file ROOT contenente gli istogrammi
  TFile *file = TFile::Open("root/data/ParticleAnalysis.root");
  if (!file || file->IsZombie())
  {
    std::cerr << "Errore nell'apertura del file ParticleAnalysis.root" << std::endl;
    return;
  }

  // Ottengo gli istogrammi necessari dal file ROOT
  TH1F *hParticleTypes = (TH1F *)file->Get("hParticleTypes");
  TH1F *hMomentum = (TH1F *)file->Get("hMomentum");
  TH1F *hPolarAngle = (TH1F *)file->Get("hPolarAngle");
  TH1F *hAzimuthalAngle = (TH1F *)file->Get("hAzimuthalAngle");

  // Verifico che tutti gli istogrammi siano stati correttamente caricati
  if (!hParticleTypes || !hMomentum || !hPolarAngle || !hAzimuthalAngle)
  {
    std::cerr << "Errore nel recupero degli istogrammi dal file!" << std::endl;
    file->Close();
    return;
  }

  // Attivo la somma dei pesi al quadrato per calcolare correttamente gli errori
  hParticleTypes->Sumw2();
  hMomentum->Sumw2();
  hPolarAngle->Sumw2();
  hAzimuthalAngle->Sumw2();

  // Imposto lo stile per visualizzare i parametri del fit nella box della statistica
  gStyle->SetOptFit(1111); // Mostra tutti i parametri del fit

  // Creo una canvas divisa in 4 pad
  TCanvas *c = new TCanvas("cDistributions", "Distributions", 1200, 800);
  c->Divide(2, 2); // Divide la canvas in 2x2 pad

  // **1) Istogramma dell'abbondanza delle particelle**

  c->cd(1); // Seleziono il primo pad
  hParticleTypes->SetTitle("Particle Abundance");
  hParticleTypes->GetXaxis()->SetTitle("Particle Type ID");
  hParticleTypes->GetYaxis()->SetTitle("Counts");
  hParticleTypes->SetLineColor(kBlue);
  hParticleTypes->Draw("E"); // Disegna l'istogramma con gli errori

  // Non eseguiamo un fit sull'abbondanza delle particelle, ma visualizziamo comunque l'istogramma

  // **2) Istogramma del modulo dell'impulso con fit esponenziale**

  c->cd(2); // Seleziono il secondo pad
  hMomentum->SetTitle("Momentum Distribution");
  hMomentum->GetXaxis()->SetTitle("Momentum (GeV/c)");
  hMomentum->GetYaxis()->SetTitle("Counts");
  hMomentum->SetLineColor(kBlue);
  hMomentum->Draw("E");

  // Definizione della funzione esponenziale per il fit
  TF1 *expFit = new TF1("expFit", "[0]*exp(-x/[1])", 0, 5); // [0]=Normalizzazione, [1]=Media
  expFit->SetParameters(1e6, 1.0);                          // Stima iniziale dei parametri
  expFit->SetLineColor(kRed);

  // Eseguo il fit sull'istogramma dell'impulso
  hMomentum->Fit("expFit", "R"); // "R" limita il fit al range della funzione

  // **3) Istogramma dell'angolo polare con fit a costante**

  c->cd(3); // Seleziono il terzo pad
  hPolarAngle->SetTitle("Polar Angle Distribution");
  hPolarAngle->GetXaxis()->SetTitle("Polar Angle #theta (rad)");
  hPolarAngle->GetYaxis()->SetTitle("Counts");
  hPolarAngle->SetLineColor(kBlue);
  hPolarAngle->Draw("E");

  // Definizione della funzione costante per il fit
  TF1 *constFitTheta = new TF1("constFitTheta", "[0]", 0, TMath::Pi()); // [0]=Costante
  constFitTheta->SetParameter(0, hPolarAngle->GetMaximum());            // Stima iniziale
  constFitTheta->SetLineColor(kRed);

  // Eseguo il fit sull'istogramma dell'angolo polare
  hPolarAngle->Fit("constFitTheta", "R"); // "R" limita il fit al range della funzione

  // **4) Istogramma dell'angolo azimutale con fit a costante**

  c->cd(4); // Seleziono il quarto pad
  hAzimuthalAngle->SetTitle("Azimuthal Angle Distribution");
  hAzimuthalAngle->GetXaxis()->SetTitle("Azimuthal Angle #phi (rad)");
  hAzimuthalAngle->GetYaxis()->SetTitle("Counts");
  hAzimuthalAngle->SetLineColor(kBlue);
  hAzimuthalAngle->Draw("E");

  // Definizione della funzione costante per il fit
  TF1 *constFitPhi = new TF1("constFitPhi", "[0]", 0, 2 * TMath::Pi()); // [0]=Costante
  constFitPhi->SetParameter(0, hAzimuthalAngle->GetMaximum());          // Stima iniziale
  constFitPhi->SetLineColor(kRed);

  // Eseguo il fit sull'istogramma dell'angolo azimutale
  hAzimuthalAngle->Fit("constFitPhi", "R"); // "R" limita il fit al range della funzione

  // **Salvo la canvas come file PDF**
  c->SaveAs("charts/plot-distributions/distributions.pdf");

  // **Pulizia della memoria**
  delete expFit;
  delete constFitTheta;
  delete constFitPhi;
  delete c;

  // Chiudo il file ROOT
  file->Close();
  delete file;

  // Messaggio di completamento
  std::cout << "Plot delle distribuzioni completato. Il grafico è stato salvato in 'charts/plot-distributions/distributions.pdf'." << std::endl;
}