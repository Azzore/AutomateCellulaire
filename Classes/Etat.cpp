#include "Etat.h"

//Constructeurs
Etat::Etat(unsigned int size) : dimension(size){
	valeur = new bool[dimension];
	for (unsigned int i = 0; i < dimension; ++i)
		valeur[i] = false;
}

Etat::Etat(const Etat& e) : dimension(e.dimension) {
	valeur = new bool[dimension];
	for (unsigned int i = 0; i < dimension; ++i)
		valeur[i] = e.valeur[i];
}

Etat& Etat::operator=(const Etat& e) {
	if (this != &e) {
		if (dimension != e.dimension) {
			delete[] valeur;
			dimension = e.dimension;
			valeur = new bool[dimension];
		}
		for (unsigned int i = 0; i < dimension; ++i)
			valeur[i] = e.valeur[i];
	}
	return *this;
}

//Destructeur
Etat::~Etat() {
	delete[] valeur;
}

//Accesseurs
bool Etat::getCellule(unsigned int i) const {
	if (i >= dimension)
		throw EtatException("Erreur : la cellule n'existe pas.");
	else
		return valeur[i];
}

void Etat::setCellule(unsigned int i, bool val) {
	if (i >= dimension)
		throw EtatException("Erreur : la cellule n'existe pas.");
	valeur[i] = val;
}

//Autre
std::ostream& operator<<(std::ostream& flux, const Etat& e) {
	unsigned int dimension = e.getDimension();

	for (unsigned int i = 0; i < dimension; ++i) {
		if (e.getCellule(i))
			flux << 'O';
		else
			flux << '_';
	}
	return flux;
}