#ifndef PARTICLETYPE_H // Questo è un "include guard". Serve a prevenire che questo file venga incluso più di una volta nel progetto.
// Se non è già stato definito PARTICLETYPE_H, lo definisce per evitare duplicazioni future.
#define PARTICLETYPE_H

#include <string> // Include la libreria standard C++ per le stringhe.
// Questo include è necessario perché la classe `ParticleType` utilizza `std::string` per il nome della particella.

// Questa è la definizione della classe `ParticleType`.
// La classe `ParticleType` descrive le proprietà di base di una particella stabile, come il nome, la massa e la carica.
class ParticleType
{
public:
  // Questo è il costruttore della classe `ParticleType`. Viene utilizzato per inizializzare un oggetto di tipo `ParticleType` con i parametri specificati.
  // Il costruttore prende tre parametri:
  // - `name`: il nome della particella (come "Pion", "Proton")
  // - `mass`: la massa della particella (un valore double che rappresenta la massa in MeV o GeV, per esempio)
  // - `charge`: la carica elettrica della particella (come +1, -1, 0)
  ParticleType(const std::string &name, double mass, int charge);

  // Questo è un metodo "getter", utilizzato per ottenere il nome della particella.
  // `const` alla fine significa che questo metodo non modifica lo stato interno dell'oggetto (non cambia le sue variabili).
  const std::string &GetName() const; // Restituisce il nome della particella.

  // Questo è un altro metodo "getter", che restituisce la massa della particella.
  // Anche questo metodo è dichiarato `const`, quindi non modifica lo stato dell'oggetto.
  double GetMass() const; // Restituisce la massa della particella.

  // Questo metodo restituisce la carica elettrica della particella.
  // Anche questo metodo è `const`, quindi non modifica i dati della particella.
  int GetCharge() const; // Restituisce la carica della particella.

  // Questo è un metodo virtuale che permette di stampare le informazioni della particella.
  // `virtual` indica che questo metodo può essere riscritto ("overrided") nelle classi che ereditano da `ParticleType` (ad esempio, `ResonanceType` può riscrivere il metodo `Print`).
  // La parola "virtual" è importante in C++ per il meccanismo di polimorfismo, che consente alle classi derivate di definire la propria versione di un metodo.
  virtual void Print() const;

protected:
  // Questi sono i dati membri (o variabili membro) della classe, che memorizzano le proprietà della particella.
  // `protected` significa che queste variabili possono essere accessibili dalle classi che ereditano da `ParticleType`, ma non da altre classi esterne.

  std::string fName; // Il nome della particella, come "Pion" o "Proton". È di tipo `std::string`.
  double fMass;      // La massa della particella. È di tipo `double`, un numero in virgola mobile che può rappresentare valori decimali.
  int fCharge;       // La carica della particella, rappresentata come un numero intero, ad esempio +1, -1, o 0 per particelle neutre.
};

#endif // PARTICLETYPE_H  // Questo chiude la guardia di inclusione, prevenendo ulteriori inclusioni multiple dello stesso file.