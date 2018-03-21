#pragma once

#include <iostream>

#include "Exceptions/EtatException.h"

class Etat {
	unsigned int dimension;
	bool* valeur;

public:
	//Constructeurs
	Etat(unsigned int = 0);
	Etat(const Etat&);
	Etat& operator=(const Etat&);
	//Destructeur
	~Etat();

	//Accesseurs
	unsigned int getDimension() const { return dimension; }
	bool getCellule(unsigned int) const;
	void setCellule(unsigned int, bool);
};

std::ostream& operator<<(std::ostream&, const Etat&);
