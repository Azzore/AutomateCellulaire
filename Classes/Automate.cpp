#include "Automate.h"

Automate::Automate(short unsigned int regle) : numero(regle){
	numeroBit = NumToNumBit(regle);
}

Automate::Automate(const std::string& bit) : numeroBit(bit) {
	if (numeroBit.length() > 8)
		throw AutomateException("La chaine de caractere est trop longue");

	while (numeroBit.length() < 8)
		numeroBit = "0" + numeroBit;

	numero = NumBitToNum(numeroBit);
}

void Automate::appliquerTransition(const Etat& pred, Etat& dest) const  {
	unsigned int dimension = pred.getDimension();
	unsigned int nb;
	dest = pred;

	for (unsigned int i = 0; i < dimension; ++i) {
		nb = 0;
		for (unsigned int j = 0; j < 3; ++j) {
			if (pred.getCellule((i + j - 1 + dimension) % dimension)) {
				if (j == 0)
					nb += 4;
				else if (j == 1)
					nb += 2;
				else if (j == 2)
					++nb;
			}
		}
		dest.setCellule(i, numeroBit[7 - nb] - '0');
	}
}

std::ostream& operator<<(std::ostream& flux, const Automate& a) {
	flux << "Automate" << a.getNumero() << " : " << a.getNumeroBit();
	return flux;
}

short unsigned int NumBitToNum(const std::string& num) {
	if (num.size() != 8)
		throw AutomateException("Numero d’automate indefini");

	int puissance = 1;
	short unsigned int numero = 0;

	for (int i = 7; i >= 0; --i) {
		if (num[i] == '1') numero += puissance;
		else if (num[i] != '0') throw AutomateException("Numero d’automate indefini");
		puissance *= 2;
	}

	return numero;
}std::string NumToNumBit(short unsigned int num) {
	if (num > 256)
		throw AutomateException("Numero d’automate indefini");

	std::string numeroBit;
	unsigned short int p = 128;
	int i = 7;

	while (i >= 0) {
		if (num >= p) { numeroBit.push_back('1'); num -= p; }
		else { numeroBit.push_back('0'); }
		i--;
		p = p / 2;
	}

	return numeroBit;
}