#include "Particle.h"      // Includiamo il file "Particle.h" per poter utilizzare la classe `Particle` e i suoi metodi.
#include "ResonanceType.h" // Includiamo il file "ResonanceType.h" per poter creare particelle risonanti.
#include <iostream>        // Includiamo la libreria standard per l'input/output in C++, necessaria per utilizzare `std::cout`.

// Funzione principale `main()`, che viene eseguita all'avvio del programma.
int main()
{
  // Aggiunta dei tipi di particelle disponibili nel sistema:
  // Il metodo statico `AddParticleType()` viene chiamato per aggiungere nuovi tipi di particelle nel sistema.

  // Aggiungiamo un "Pion+" con massa 0.139 GeV e carica +1 all'array statico `fParticleTypes` in Particle.
  Particle::AddParticleType(new ParticleType("Pion+", 0.139, +1));

  // Aggiungiamo un "Pion-" con massa 0.139 GeV e carica -1.
  Particle::AddParticleType(new ParticleType("Pion-", 0.139, -1));

  // Aggiungiamo un tipo di particella risonante, "K*" con massa 0.892 GeV, carica neutra e una larghezza di risonanza di 0.05.
  Particle::AddParticleType(new ResonanceType("K*", 0.892, 0, 0.05));

  // Stampa dei tipi di particelle aggiunti:
  // Il metodo statico `PrintArray()` viene utilizzato per stampare tutti i tipi di particelle aggiunte finora.
  std::cout << "=== Tipi di particelle aggiunti ===" << std::endl;
  Particle::PrintArray(); // Mostra tutte le particelle nell'array `fParticleTypes`.

  // Creazione di due oggetti di tipo `Particle`:
  // Creiamo una particella `p1` di tipo "Pion+" con un impulso iniziale di (1.0, 2.0, 3.0).
  Particle p1(1.0, 2.0, 3.0, 0); // L'indice 0 corrisponde al tipo "Pion+" nell'array `fParticleTypes`.

  // Creiamo un'altra particella `p2` di tipo "K*" con un impulso iniziale di (0.5, 1.5, -0.5).
  Particle p2(0.5, 1.5, -0.5, 2); // L'indice 2 corrisponde al tipo "K*" nell'array `fParticleTypes`.

  // Test di impostazione dell'impulso per `p1`:
  // Cambiamo l'impulso di `p1` utilizzando il metodo `SetP()`. Impostiamo l'impulso a (5.0, 5.0, 5.0).
  p1.SetP(5.0, 5.0, 5.0);
  std::cout << "Impulso aggiornato per p1: (5.0, 5.0, 5.0)" << std::endl;

  // Verifica dell'indice di `p1`:
  // Il metodo `GetIndex()` viene utilizzato per verificare l'indice del tipo di particella associato a `p1`.
  // Dovrebbe stampare "0", poiché `p1` è di tipo "Pion+".
  std::cout << "Indice p1 (dovrebbe essere 0 - Pion+): " << p1.GetIndex() << std::endl;

  // Test del metodo `FindParticle()`:
  // Verifichiamo se possiamo trovare l'indice della particella "Pion+" nell'array `fParticleTypes` tramite il nome.
  std::cout << "=== Verifica metodo FindParticle ===" << std::endl;
  int pionIndex = Particle::FindParticle("Pion+");
  std::cout << "Pion+ trovato all'indice: " << pionIndex << std::endl;

  // Proviamo a cercare una particella che non esiste:
  // Dato che "Unknown" non è presente nell'array `fParticleTypes`, ci aspettiamo che il metodo ritorni -1.
  int unknownIndex = Particle::FindParticle("Unknown");
  std::cout << "Unknown Particle trovato all'indice (dovrebbe essere -1): " << unknownIndex << std::endl;

  // Test del calcolo dell'energia per `p1` e `p2`:
  // Il metodo `CalculateEnergy()` calcola l'energia totale di una particella usando la formula relativistica \( E^2 = p^2 + m^2 \).
  std::cout << "=== Calcolo dell'energia per le particelle ===" << std::endl;
  std::cout << "Energia di p1 (Pion+): " << p1.CalculateEnergy() << std::endl;
  std::cout << "Energia di p2 (K*): " << p2.CalculateEnergy() << std::endl;

  // Test della risonanza `K*`:
  // Cambiamo l'impulso di `p2` utilizzando `SetP()` e verifichiamo che l'energia cambi di conseguenza.
  p2.SetP(1.0, 0.5, 0.2); // Cambiamo l'impulso di `p2`.
  std::cout << "Energia di p2 dopo cambio impulso: " << p2.CalculateEnergy() << std::endl;

  // Fine dei test:
  std::cout << "=== Fine dei test ===" << std::endl;

  return 0; // Il programma termina restituendo 0, indicando che è stato eseguito con successo.
}