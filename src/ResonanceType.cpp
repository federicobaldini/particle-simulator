#include "ResonanceType.h"
#include <iostream>

ResonanceType::ResonanceType(const std::string &name, double mass, int charge, double width)
    : ParticleType(name, mass, charge), fWidth(width) {}

// Metodo che restituisce la larghezza della risonanza.
// return: valore della larghezza di risonanza (fWidth)
double ResonanceType::GetWidth() const
{
  return fWidth;
}

// Metodo per stampare tutte le proprietà della particella, inclusa la larghezza di risonanza.
// Chiama il metodo Print della classe base per stampare nome, massa e carica,
// quindi aggiunge la larghezza della risonanza.
void ResonanceType::Print() const
{
  ParticleType::Print();                         // Chiamata al metodo della classe base per stampare le proprietà comuni
  std::cout << "Width: " << fWidth << std::endl; // Stampa la larghezza della risonanza
}