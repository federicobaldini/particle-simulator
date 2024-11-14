#include "TFile.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TKey.h"
#include "TString.h"
#include <iostream>
#include <sys/stat.h>

void save_histograms()
{
  // Crea la cartella "charts" se non esiste
  struct stat info;
  if (stat("charts", &info) != 0)
  {
    std::cout << "Creazione della cartella 'charts'..." << std::endl;
    system("mkdir -p charts"); // Comando per creare la cartella
  }

  // Apri il file ROOT contenente gli istogrammi
  TFile *file = TFile::Open("../data/ParticleAnalysis.root");
  if (!file || file->IsZombie())
  {
    std::cout << "Errore nell'apertura del file!" << std::endl;
    return;
  }

  // Itera su tutti gli oggetti nel file
  TIter next(file->GetListOfKeys());
  TKey *key;
  while ((key = (TKey *)next()))
  {
    // Leggi l'oggetto
    TObject *obj = key->ReadObj();
    // Verifica se l'oggetto è un istogramma 1D
    if (obj->InheritsFrom("TH1"))
    {
      TH1 *hist = (TH1 *)obj;
      // Crea un canvas per disegnare l'istogramma
      TCanvas *c = new TCanvas();
      hist->Draw();
      // Salva l'istogramma come PDF nella cartella "charts" con il nome dell'istogramma
      TString pdfName = TString::Format("../../charts/%s.pdf", hist->GetName());
      c->SaveAs(pdfName);
      delete c; // Elimina il canvas per liberare memoria
    }
  }
  file->Close(); // Chiudi il file ROOT
  std::cout << "Tutti gli istogrammi sono stati salvati nella cartella 'charts' come PDF." << std::endl;
}