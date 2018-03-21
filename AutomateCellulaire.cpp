#include <iostream>

#include "Classes/Etat.h"
#include "Classes/Automate.h"
#include "Classes/Simulateur.h"

using namespace std;

int main() {

	Automate a(113);

	cout << "automate " << a << endl;

	Etat e(22); e.setCellule(11, true);

	Simulateur s(a, e);

	cout << e << endl;

	for (unsigned int i = 0; i < 10; i++) {
		s.next();
		cout << s.dernier() << endl;
	}

	exit(EXIT_SUCCESS);
}