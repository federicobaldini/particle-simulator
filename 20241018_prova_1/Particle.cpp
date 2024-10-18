#include "Particle.h"
#include "ResonanceType.h"
#include "ParticleType.h"
#include <iostream>
#include <cmath>

// Inizializzazione dell'array statico di puntatori a ParticleType
ParticleType *Particle::fParticleType[Particle::fMaxNumParticleType] = {nullptr};

// Inizializzazione del contatore statico per il numero di tipi di particelle
int Particle::fNParticleType = 0;

// Costruttore parametrico che inizializza il tipo di particella e le componenti dell'impulso
Particle::Particle(const std::string &name, double px, double py, double pz)
    : fPx(px), fPy(py), fPz(pz)
{
  fIndex = FindParticle(name); // Cerca il tipo di particella nell'array
  if (fIndex == -1)
  {
    std::cout << "Particle type " << name << " not found!" << std::endl;
  }
}

// Metodo privato che cerca il tipo di particella nell'array fParticleType
int Particle::FindParticle(const std::string &name)
{
  for (int i = 0; i < fNParticleType; ++i)
  {
    if (fParticleType[i]->GetName() == name)
    {
      return i; // Restituisce l'indice se il nome corrisponde
    }
  }
  return -1; // Restituisce -1 se non trova corrispondenza
}

// Getter per l'indice del tipo di particella
int Particle::GetIndex() const
{
  return fIndex;
}

// Metodo statico per aggiungere un nuovo tipo di particella all'array fParticleType
void Particle::AddParticleType(const std::string &name, double mass, int charge, double width)
{
  if (fNParticleType >= fMaxNumParticleType)
  {
    std::cout << "Cannot add more particle types, maximum reached!" << std::endl;
    return;
  }

  // Verifica se il tipo di particella esiste già
  if (FindParticle(name) != -1)
  {
    std::cout << "Particle type " << name << " already exists!" << std::endl;
    return;
  }

  // Aggiunge una nuova particella all'array, utilizzando il costruttore appropriato
  if (width == 0)
  {
    fParticleType[fNParticleType] = new ParticleType(name, mass, charge);
  }
  else
  {
    fParticleType[fNParticleType] = new ResonanceType(name, mass, charge, width);
  }

  ++fNParticleType; // Incrementa il contatore di tipi di particella
}

// Metodo per impostare l'indice del tipo di particella utilizzando il nome
void Particle::SetIndex(const std::string &name)
{
  fIndex = FindParticle(name);
  if (fIndex == -1)
  {
    std::cout << "Particle type " << name << " not found!" << std::endl;
  }
}

// Metodo per impostare l'indice del tipo di particella utilizzando direttamente l'indice
void Particle::SetIndex(int index)
{
  if (index >= 0 && index < fNParticleType)
  {
    fIndex = index;
  }
  else
  {
    std::cout << "Invalid particle index!" << std::endl;
  }
}

// Metodo per stampare le proprietà della particella
void Particle::Print() const
{
  if (fIndex != -1 && fIndex < fNParticleType)
  {
    fParticleType[fIndex]->Print(); // Stampa le proprietà del tipo di particella
  }
  std::cout << "Px: " << fPx << ", Py: " << fPy << ", Pz: " << fPz << std::endl; // Stampa l'impulso
}

// Metodo per settare le componenti dell'impulso
void Particle::SetP(double px, double py, double pz)
{
  fPx = px;
  fPy = py;
  fPz = pz;
}

// Metodo che restituisce la massa della particella
double Particle::GetMass() const
{
  if (fIndex != -1)
  {
    return fParticleType[fIndex]->GetMass();
  }
  return 0;
}

// Metodo che calcola l'energia totale della particella
double Particle::GetEnergy() const
{
  double mass = GetMass();
  double p2 = fPx * fPx + fPy * fPy + fPz * fPz; // Calcola il quadrato dell'impulso
  return std::sqrt(mass * mass + p2);            // Formula relativistica dell'energia totale
}

// Metodo che calcola la massa invariante tra questa particella e un'altra particella
double Particle::InvMass(const Particle &other) const
{
  double e1 = GetEnergy();
  double e2 = other.GetEnergy();
  double px_total = fPx + other.GetPx();
  double py_total = fPy + other.GetPy();
  double pz_total = fPz + other.GetPz();
  double p2_total = px_total * px_total + py_total * py_total + pz_total * pz_total;
  double mass_inv = std::sqrt((e1 + e2) * (e1 + e2) - p2_total); // Formula per la massa invariante
  return mass_inv;
}