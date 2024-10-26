#include "Particle.h"
#include "ResonanceType.h"
#include "ParticleType.h"
#include <iostream>
#include <cmath>
#include <cstdlib> // Per RAND_MAX e rand()

// Inizializzazione dell'array statico di puntatori a ParticleType
ParticleType *Particle::fParticleType[Particle::fMaxNumParticleType] = {nullptr};

// Inizializzazione del contatore statico per il numero di tipi di particelle
int Particle::fNParticleType = 0;

// Costruttore parametrico che inizializza il tipo di particella e le componenti dell'impulso
Particle::Particle(const std::string &name, double px, double py, double pz)
    : fPx(px), fPy(py), fPz(pz)
{
  fIndex = FindParticleType(name); // Cerca il tipo di particella nell'array
  if (fIndex == -1)
  {
    std::cout << "Particle type " << name << " not found!" << std::endl;
  }
}

// Metodo privato che cerca il tipo di particella nell'array fParticleType
int Particle::FindParticleType(const std::string &name)
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
int Particle::GetParticleTypeIndex() const
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
  if (FindParticleType(name) != -1)
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
void Particle::SetParticleTypeIndex(const std::string &name)
{
  fIndex = FindParticleType(name);
  if (fIndex == -1)
  {
    std::cout << "Particle type " << name << " not found!" << std::endl;
  }
}

// Metodo per impostare l'indice del tipo di particella utilizzando direttamente l'indice
void Particle::SetParticleTypeIndex(int index)
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
void Particle::SetPulse(double px, double py, double pz)
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
double Particle::InvariantMass(const Particle &other) const
{
  double e1 = GetEnergy();
  double e2 = other.GetEnergy();
  double px_total = fPx + other.GetPulseX();
  double py_total = fPy + other.GetPulseY();
  double pz_total = fPz + other.GetPulseZ();
  double p2_total = px_total * px_total + py_total * py_total + pz_total * pz_total;
  double mass_inv = std::sqrt((e1 + e2) * (e1 + e2) - p2_total); // Formula per la massa invariante
  return mass_inv;
}

// Metodo Decay2body per la decadenza in due particelle figlie
int Particle::Decay2body(Particle &dau1, Particle &dau2) const
{
  if (GetMass() == 0.0)
  {
    std::cerr << "Decayment cannot be performed if mass is zero\n";
    return 1;
  }

  double massMot = GetMass();
  double massDau1 = dau1.GetMass();
  double massDau2 = dau2.GetMass();

  // Effetto larghezza: verifica se il tipo di particella è una ResonanceType
  if (fIndex > -1)
  {
    ResonanceType *resonance = dynamic_cast<ResonanceType *>(fParticleType[fIndex]);
    if (resonance)
    { // Se il cast è riuscito, l'oggetto è una ResonanceType
      float x1, x2, w, y1;
      double invnum = 1. / RAND_MAX;
      do
      {
        x1 = 2.0 * rand() * invnum - 1.0;
        x2 = 2.0 * rand() * invnum - 1.0;
        w = x1 * x1 + x2 * x2;
      } while (w >= 1.0);

      w = sqrt((-2.0 * log(w)) / w);
      y1 = x1 * w;

      massMot += resonance->GetWidth() * y1; // Accede a GetWidth solo se è ResonanceType
    }
  }

  if (massMot < massDau1 + massDau2)
  {
    std::cerr << "Decayment cannot be performed because mass is too low in this channel\n";
    return 2;
  }

  double pout = sqrt((massMot * massMot - (massDau1 + massDau2) * (massDau1 + massDau2)) *
                     (massMot * massMot - (massDau1 - massDau2) * (massDau1 - massDau2))) /
                (massMot * 0.5);

  double norm = 2 * M_PI / RAND_MAX;
  double phi = rand() * norm;
  double theta = rand() * norm * 0.5 - M_PI / 2.;

  // Imposta il momento delle particelle figlie
  dau1.SetPulse(pout * sin(theta) * cos(phi), pout * sin(theta) * sin(phi), pout * cos(theta));
  dau2.SetPulse(-pout * sin(theta) * cos(phi), -pout * sin(theta) * sin(phi), -pout * cos(theta));

  double energy = sqrt(fPx * fPx + fPy * fPy + fPz * fPz + massMot * massMot);
  double bx = fPx / energy;
  double by = fPy / energy;
  double bz = fPz / energy;

  // Applica il boost alle particelle figlie
  dau1.Boost(bx, by, bz);
  dau2.Boost(bx, by, bz);

  return 0;
}

// Metodo Boost
void Particle::Boost(double bx, double by, double bz)
{
  double energy = GetEnergy();
  double b2 = bx * bx + by * by + bz * bz;
  double gamma = 1.0 / sqrt(1.0 - b2);
  double bp = bx * fPx + by * fPy + bz * fPz;
  double gamma2 = (b2 > 0) ? (gamma - 1.0) / b2 : 0.0;

  fPx += gamma2 * bp * bx + gamma * bx * energy;
  fPy += gamma2 * bp * by + gamma * by * energy;
  fPz += gamma2 * bp * bz + gamma * bz * energy;
}