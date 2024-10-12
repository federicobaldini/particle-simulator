#include "ParticleType.h" // Include il file header "ParticleType.h" che contiene la dichiarazione della classe `ParticleType`.
// Questo include ci consente di utilizzare i metodi e i membri della classe `ParticleType` definiti nel file header.

#include <iostream> // Include la libreria standard per l'input/output in C++.
// Ci permette di usare `std::cout` per stampare informazioni sullo schermo.

// Definizione del costruttore della classe `ParticleType`.
// Questo costruttore inizializza i membri della classe con i valori forniti (name, mass, charge).
ParticleType::ParticleType(const std::string &name, double mass, int charge)
    : fName(name), fMass(mass), fCharge(charge) {}

// Definizione del metodo `GetName()` della classe `ParticleType`.
// Questo metodo restituisce una "riferimento costante" alla stringa `fName`, che contiene il nome della particella.
// Il riferimento costante evita di copiare la stringa intera e garantisce che il nome non possa essere modificato fuori dal metodo.
const std::string &ParticleType::GetName() const
{
  return fName; // Restituisce il nome della particella.
}

// Definizione del metodo `GetMass()` della classe `ParticleType`.
// Questo metodo restituisce la massa della particella memorizzata nella variabile `fMass`.
// Il metodo è dichiarato `const`, il che significa che non modifica alcun dato membro della classe.
double ParticleType::GetMass() const
{
  return fMass; // Restituisce la massa della particella.
}

// Definizione del metodo `GetCharge()` della classe `ParticleType`.
// Questo metodo restituisce la carica della particella memorizzata nella variabile `fCharge`.
// Il metodo è dichiarato `const`, il che significa che non modifica alcun dato membro della classe.
int ParticleType::GetCharge() const
{
  return fCharge; // Restituisce la massa della particella.
}

// Definizione del metodo `Print()` della classe `ParticleType`.
// Questo metodo stampa sullo schermo il nome, la massa e la carica della particella.
void ParticleType::Print() const
{
  // Qui stiamo utilizzando `std::cout` per stampare le informazioni della particella.
  // Viene stampato il nome (`fName`), la massa (`fMass`) e la carica (`fCharge`), separati da virgole.
  std::cout << "Name: " << fName << ", Mass: " << fMass << ", Charge: " << fCharge << std::endl;
  // `std::endl` inserisce un ritorno a capo (nuova linea) alla fine della stampa.
}