#pragma once

#include <iostream>
#include <string>

#include "Etat.h"
#include "Exceptions/AutomateException.h"

class Automate {
	friend class AutomateManager;
	short unsigned int numero = 0;
	std::string numeroBit;

	//Constructeurs
	Automate(short unsigned int);
	Automate(const std::string&);

public:
	//Accesseurs
	unsigned int getNumero() const { return numero; }
	std::string getNumeroBit() const { return numeroBit; }
	//Methodes
	void appliquerTransition(const Etat&, Etat&) const;
};	

std::ostream& operator<<(std::ostream&, const Automate&);

short unsigned int NumBitToNum(const std::string& num);

std::string NumToNumBit(short unsigned int num);

