#ifndef RESONANCETYPE_H // Questo è un "include guard", una protezione per evitare che questo file venga incluso più di una volta nel progetto.
#define RESONANCETYPE_H // Se non è già definito RESONANCETYPE_H, lo definisce per evitare duplicati futuri.

#include "ParticleType.h" // Qui stiamo includendo il file "ParticleType.h" che contiene la definizione della classe base `ParticleType`.
// Questo include è necessario perché la classe ResonanceType eredita da ParticleType.

// Definizione della classe ResonanceType, che è una sottoclasse di ParticleType.
// Questo significa che ResonanceType eredita tutte le proprietà e i metodi della classe ParticleType.
class ResonanceType : public ParticleType // `public` significa che i membri pubblici di ParticleType rimarranno pubblici in ResonanceType.
{
public:
  // Questo è il costruttore della classe ResonanceType.
  // Un costruttore è una funzione speciale che viene chiamata quando crei un nuovo oggetto della classe.
  // Il costruttore qui prende come parametri:
  // - `name`: il nome della particella
  // - `mass`: la massa della particella
  // - `charge`: la carica della particella (come +1 o -1)
  // - `width`: la larghezza della risonanza (un valore che rappresenta quanto la particella è instabile)
  ResonanceType(const std::string &name, double mass, int charge, double width);

  // Questo è un metodo pubblico che restituisce il valore della larghezza della risonanza (fWidth).
  // `const` dopo la dichiarazione del metodo indica che questo metodo non modifica lo stato dell'oggetto (non cambia i suoi attributi).
  double GetWidth() const;

  // Questo è un metodo che stampa le informazioni sulla particella risonante, inclusi il nome, la massa, la carica e la larghezza.
  // `override` indica che questa funzione riscrive (override) una funzione con lo stesso nome presente nella classe base (ParticleType).
  void Print() const override;

private:
  // Questa è una variabile membro privata della classe, chiamata `fWidth`.
  // È di tipo `double` e memorizza la larghezza della risonanza della particella.
  // Le variabili membro private non possono essere accessibili direttamente dall'esterno della classe, ma solo attraverso i metodi pubblici.
  double fWidth;
};

#endif // RESONANCETYPE_H  // Fine della protezione dell'inclusione multipla del file.