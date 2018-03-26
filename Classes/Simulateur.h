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

	Simulateur(const Simulateur&) = delete;
	Simulateur operator=(const Simulateur&) = delete;

	void run(unsigned int);
	void setEtatDepart(const Etat&);
	void next();
	void reset();
	const Etat& dernier();
	unsigned int getRangDernier() const { return rang; }

	class Iterator {
		friend class Simulateur;
		Simulateur* sim = nullptr;
		int i = 0;
		Iterator(Simulateur* s) : sim(s), i(s->rang) {}
		Iterator(Simulateur* s, int j) : sim(s), i(j) {};
	public:
		Iterator() {};
		bool isDone () const;
		void next();
		Etat& current() const;
		Iterator& operator++() { next(); return *this; };
		Etat& operator*() const { return current(); }
		bool operator!=(Iterator);
	};

	class ConstIterator {
		friend class Simulateur;
		const Simulateur* sim = nullptr;
		int i = 0;
		ConstIterator(const Simulateur* s) : sim(s), i(s->rang) {}
		ConstIterator(const Simulateur* s, int j) : sim(s), i(j) {};
	public:
		ConstIterator() {};
		bool isDone() const;
		void next();
		Etat& current() const;
		ConstIterator& operator++() { next(); return *this; };
		Etat& operator*() const { return current(); }
	};

	Iterator begin() { return Iterator(this); }
	ConstIterator begin() const { return ConstIterator(this); }

	Iterator end();
	ConstIterator end() const;

};

