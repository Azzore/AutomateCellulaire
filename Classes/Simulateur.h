#pragma once

#include "Automate.h"
#include "Etat.h"
#include "Exceptions/SimulateurException.h"

class Simulateur {
	const Automate& automate;
	Etat** etats;
	unsigned int nbMaxEtats;
	unsigned int rang = 0;
	const Etat* depart;

public:
	Simulateur(const Automate&, unsigned int = 2);
	Simulateur(const Automate&, const Etat&, unsigned int = 2);
	~Simulateur();

	void run(unsigned int);
	void setEtatDepart(const Etat&);
	void next();
	void reset();
	const Etat& dernier();
	unsigned int getRangDernier() const { return rang; }
};

