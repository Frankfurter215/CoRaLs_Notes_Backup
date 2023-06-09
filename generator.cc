#include "generator.hh"
MyPrimaryGenerator::MyPrimaryGenerator()
{
	fParticleGun = new G4ParticleGun(1); //1 particle per event

	G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
	G4ParticleDefinition *particle = particleTable->FindParticle("geantino");

	G4ThreeVector pos(0., 0., 0.); //created in center of mother volume
	G4ThreeVector mom(0., 0., 1.); //sets momentum direction in positive set direction

	fParticleGun->SetParticlePosition(pos);
	fParticleGun->SetParticleMomentumDirection(mom); //again, just sets the direction of momentum doesn't create momentum
	fParticleGun->SetParticleMomentum(10.*GeV); //set particle at very high momentum (original units meV)
	fParticleGun->SetParticleDefinition(particle);

}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
	delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
	G4ParticleDefinition *particle = fParticleGun->GetParticleDefinition();

	if(particle == G4Geantino::Geantino())
	{
		G4int Z = 1;
		G4int A = 1;

		G4double charge = 1. *eplus;
		G4double energy = 1000. *keV;

		G4ParticleDefinition *ion = G4IonTable::GetIonTable() -> GetIon(Z, A, energy);
		fParticleGun->SetParticleDefinition(ion);
		fParticleGun->SetParticleCharge(charge);
	}

	fParticleGun->GeneratePrimaryVertex(anEvent);
}
