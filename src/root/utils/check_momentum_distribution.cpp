// Macro per verificare se la distribuzione del modulo dell'impulso è esponenziale
// e consistente con la media attesa (1 GeV).

#include "TFile.h"
#include "TH1F.h"
#include "TF1.h"
#include "TCanvas.h"
#include <iostream>

void check_momentum_distribution()
{
  // Apro il file ROOT contenente gli istogrammi.
  TFile *file = TFile::Open("root/data/ParticleAnalysis.root");
  if (!file || file->IsZombie()) // Controlla se il file è stato aperto correttamente.
  {
    std::cerr << "Errore nell'apertura del file ParticleAnalysis.root" << std::endl;
    return;
  }

  // Ottengo l'istogramma del modulo dell'impulso.
  TH1F *hMomentum = (TH1F *)file->Get("hMomentum");
  if (!hMomentum) // Verifica se l'istogramma esiste.
  {
    std::cerr << "Istogramma hMomentum non trovato nel file!" << std::endl;
    file->Close();
    return;
  }

  // Definizione della funzione esponenziale per il fit:
  // - `[0]` è il fattore di normalizzazione (altezza iniziale).
  // - `[1]` rappresenta la media della distribuzione esponenziale.
  // Modifica dell'intervallo di fit per escludere la regione a basso impulso
  TF1 *expFit = new TF1("expFit", "[0]*exp(-x/[1])", 0.5, 5); // Fit da 0.5 GeV a 5 GeV
  expFit->SetParameter(1, 1.0);                               // Imposto il valore iniziale della media (1 GeV).
  expFit->SetLineColor(kRed);                                 // Imposto il colore della curva di fit (rosso).
  expFit->SetLineWidth(2);                                    // Imposto lo spessore della linea.

  // Creo un canvas per la visualizzazione
  TCanvas *c1 = new TCanvas("cMomentum", "Fit Momentum", 800, 600);

  // Disegno l'istogramma dell'impulso
  hMomentum->SetTitle("Distribuzione del Modulo dell'Impulso con Fit Esponenziale");
  hMomentum->GetXaxis()->SetTitle("Impulso (GeV/c)");
  hMomentum->GetYaxis()->SetTitle("Conteggi");
  hMomentum->Draw("E"); // Disegna l'istogramma con gli errori

  // Eseguo il fit dell'istogramma hMomentum con la funzione esponenziale nell'intervallo specificato
  std::cout << "Fit della distribuzione del modulo dell'impulso (hMomentum):" << std::endl;
  hMomentum->Fit("expFit", "R"); // 'R' per rispettare il range impostato nella funzione

  // Disegno la funzione di fit sovrapposta
  expFit->Draw("Same");

  // Ottengo e stampo i risultati del fit:
  double chi2 = expFit->GetChisquare();
  int ndf = expFit->GetNDF();
  double prob = expFit->GetProb();

  double param0 = expFit->GetParameter(0);
  double param0Error = expFit->GetParError(0);
  double param1 = expFit->GetParameter(1);
  double param1Error = expFit->GetParError(1);

  // Stampa dei parametri del fit e delle statistiche.
  std::cout << "Parametro del fit [0] (Normalizzazione): " << param0 << " ± " << param0Error << std::endl;
  std::cout << "Parametro del fit [1] (Media): " << param1 << " ± " << param1Error << std::endl;
  std::cout << "Chi2/NDF: " << chi2 << "/" << ndf << " = " << chi2 / ndf << std::endl;
  std::cout << "Probabilità del fit: " << prob << std::endl;

  // Verifico se la media ottenuta è consistente con il valore atteso (1 GeV).
  double expectedMean = 1.0; // Valore teorico della media.
  if (std::abs(param1 - expectedMean) <= param1Error)
  {
    std::cout << "La media ottenuta è consistente con la media attesa (" << expectedMean << " GeV) entro gli errori." << std::endl;
  }
  else
  {
    std::cout << "La media ottenuta NON è consistente con la media attesa (" << expectedMean << " GeV)." << std::endl;
  }

  // Salvo il risultato del fit come file PDF per un'analisi visiva.
  c1->SaveAs("charts/check-momentum-distribution/hMomentum_fit.pdf"); // Salva nella directory corrente

  // Libero la memoria e chiudo le risorse.
  delete c1;     // Elimina il canvas creato.
  file->Close(); // Chiude il file ROOT.
  delete file;   // Libera la memoria del file.
  delete expFit; // Elimina la funzione di fit.

  // Messaggio di completamento dell'analisi.
  std::cout << "Verifica della distribuzione del modulo dell'impulso completata." << std::endl;
}