// Macro per salvare tutti gli istogrammi presenti in un file ROOT
// come file PDF nella cartella "charts".

#include "TFile.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TKey.h"
#include "TString.h"
#include <iostream>
#include <sys/stat.h>

void save_histograms()
{
  // Controllo se la cartella "charts" esiste.
  // Se non esiste, la creo utilizzando il comando di sistema "mkdir".
  struct stat info;
  if (stat("charts", &info) != 0)
  {
    std::cout << "Creazione della cartella 'charts'..." << std::endl;
    system("mkdir -p charts"); // "-p" assicura che la cartella venga creata se non esiste
  }

  // Apro il file ROOT contenente gli istogrammi.
  TFile *file = TFile::Open("root/data/ParticleAnalysis.root");
  if (!file || file->IsZombie()) // Controlla se il file è aperto correttamente o è corrotto.
  {
    std::cout << "Errore nell'apertura del file!" << std::endl;
    return;
  }

  // Itero su tutti gli oggetti salvati nel file ROOT.
  TIter next(file->GetListOfKeys());
  TKey *key;
  while ((key = (TKey *)next())) // Scorre ogni chiave (oggetto salvato) nel file.
  {
    // Legge l'oggetto associato alla chiave corrente.
    TObject *obj = key->ReadObj();

    // Verifica se l'oggetto corrente è un istogramma 1D (classe TH1).
    if (obj->InheritsFrom("TH1"))
    {
      TH1 *hist = (TH1 *)obj; // Effettua il cast a TH1.

      // Crea un canvas per visualizzare l'istogramma.
      TCanvas *c = new TCanvas();
      hist->Draw(); // Disegna l'istogramma sul canvas.

      // Genera il nome del file PDF basandosi sul nome dell'istogramma.
      TString pdfName = TString::Format("charts/%s.pdf", hist->GetName());

      // Salva l'istogramma come PDF nella cartella "charts".
      c->SaveAs(pdfName);

      // Rimuove il canvas per liberare la memoria.
      delete c;
    }
  }

  // Chiudo il file ROOT dopo aver processato tutti gli oggetti.
  file->Close();

  // Messaggio di completamento.
  std::cout << "Tutti gli istogrammi sono stati salvati nella cartella 'charts' come PDF." << std::endl;
}