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

bool Simulateur::Iterator::isDone() const {
	return sim == nullptr || (i == -1 && sim->rang < sim->nbMaxEtats) || i == sim->rang - sim->nbMaxEtats;
}

void Simulateur::Iterator::next() {
	if (isDone())
		throw SimulateurException("Error, next on an iterator");
	--i;
	if (i == -1 && sim->rang >= sim->nbMaxEtats)
		i = sim->nbMaxEtats - 1;
}

Etat& Simulateur::Iterator::current() const {
	if (isDone())
		throw SimulateurException("Current on iterator");
	return *sim->etats[i%sim->nbMaxEtats];
}

bool Simulateur::ConstIterator::isDone() const {
	return sim == nullptr || (i == -1 && sim->rang < sim->nbMaxEtats) || i == sim->rang - sim->nbMaxEtats;
}

void Simulateur::ConstIterator::next()  {
	if (isDone())
		throw SimulateurException("Error, next on an iterator");
	--i;
	if (i == -1 && sim->rang >= sim->nbMaxEtats)
		i = sim->nbMaxEtats - 1;
}

Etat& Simulateur::ConstIterator::current() const {
	if (isDone())
		throw SimulateurException("Current on iterator");
	return *sim->etats[i%sim->nbMaxEtats];
}

bool Simulateur::Iterator::operator!=(Iterator it) {
	return sim != it.sim || i != it.i;
}

Simulateur::Iterator Simulateur::end() {
	if (rang < nbMaxEtats)
		return Iterator(this, -1);
	return Iterator(this, rang - nbMaxEtats);
}

Simulateur::ConstIterator Simulateur::end() const {
	if (rang < nbMaxEtats)
		return ConstIterator(this, -1);
	return ConstIterator(this, rang - nbMaxEtats);
}