#include "Simulateur.h"

Simulateur::Simulateur(const Automate& autom, unsigned int buf) : automate(autom), nbMaxEtats(buf) {
	etats = new Etat*[nbMaxEtats];

	for (unsigned int i = 0; i < nbMaxEtats; ++i)
		etats[i] = nullptr;
}

Simulateur::Simulateur(const Automate& autom, const Etat& e, unsigned int buf) : automate(autom), depart(&e), nbMaxEtats(buf) {
	etats = new Etat*[nbMaxEtats];

	for (unsigned int i = 0; i < nbMaxEtats; ++i)
		etats[i] = nullptr;

	etats[0] = new Etat(e);
}

Simulateur::~Simulateur() {
	for (unsigned int i = 0; i < nbMaxEtats; ++i)
		delete etats[i];

	delete[] etats;
}

void Simulateur::setEtatDepart(const Etat& e) {
	depart = &e;
	reset();
}

void Simulateur::next() {
	
	unsigned int courant = rang % nbMaxEtats;
	++rang;
	unsigned int nouveau = rang % nbMaxEtats;
	

	if (etats[nouveau] == nullptr)
		etats[nouveau] = new Etat;

	automate.appliquerTransition(*etats[courant], *etats[nouveau]);
}

void Simulateur::run(unsigned int n) {
	for (unsigned int i = 0; i < n; ++i)
		next();
}

const Etat& Simulateur::dernier() {
	if (depart == nullptr)
		throw SimulateurException("Pas de depart");

	return *etats[rang % nbMaxEtats];
}

void Simulateur::reset() {
	if (depart == nullptr)
		throw SimulateurException("Pas de depart");

	rang = 0;
	if (etats[0] == nullptr)
		etats[0] = new Etat(*depart);
	else
		*etats[0] = *depart;
}