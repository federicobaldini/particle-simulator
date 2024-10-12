#include "ResonanceType.h" // Qui stiamo includendo il file header "ResonanceType.h" per poter utilizzare la classe ResonanceType.
// Questo include è necessario per dire al compilatore dove trovare la dichiarazione della classe ResonanceType e la sua relazione con ParticleType.

#include <iostream> // Include la libreria standard per l'input/output in C++.
// Questo ci permette di utilizzare `std::cout` per stampare messaggi sullo schermo.

// Questa è la definizione del costruttore di ResonanceType.
// Un costruttore è una funzione speciale che viene chiamata automaticamente quando viene creato un nuovo oggetto della classe.
// Il costruttore di ResonanceType prende quattro parametri:
// - `name`: il nome della particella (tipo stringa)
// - `mass`: la massa della particella (tipo double)
// - `charge`: la carica della particella (tipo int)
// - `width`: la larghezza della risonanza (tipo double)
ResonanceType::ResonanceType(const std::string &name, double mass, int charge, double width)
    : ParticleType(name, mass, charge), // Questa parte chiama il costruttore della classe base `ParticleType`, passando i valori `name`, `mass`, e `charge`.
                                        // Questo processo è chiamato "costruttore di inizializzazione di base". In pratica, prima inizializziamo la parte "ParticleType" di ResonanceType.
      fWidth(width)                     // Qui stiamo inizializzando il membro `fWidth` della classe ResonanceType con il valore passato (larghezza della risonanza).
{
}
// Questo blocco `{}` rappresenta il corpo del costruttore, che in questo caso è vuoto perché tutta l'inizializzazione avviene nella lista di inizializzazione sopra.

// Definizione del metodo `Print()` della classe ResonanceType.
// `Print()` è un metodo che stampa le proprietà della particella (nome, massa, carica e larghezza della risonanza).
// Il metodo è contrassegnato come `const`, il che significa che non modifica lo stato dell'oggetto (non cambia nessun attributo della classe).
void ResonanceType::Print() const
{
  // Questo chiama il metodo `Print()` della classe base `ParticleType`.
  // Poiché ResonanceType eredita da ParticleType, possiamo riutilizzare il metodo `Print()` di ParticleType per stampare nome, massa e carica.
  ParticleType::Print();

  // Questo comando stampa la larghezza della risonanza della particella (fWidth).
  // `std::cout` è utilizzato per stampare output sullo schermo.
  // In questo caso, stampa il valore della larghezza della risonanza (fWidth) seguito da un'interruzione di linea (`std::endl`).
  std::cout << "Width: " << fWidth << std::endl;
}