#include <iostream>

#include "Classes/Etat.h"
#include "Classes/Automate.h"
#include "Classes/Simulateur.h"
#include "Classes/AutomateManager.h"

using namespace std;

//Bonjour

void afficherEtModifierEtats(Simulateur& s) {
	for (Simulateur::Iterator it = s.begin(); it != s.end(); ++it)
		std::cout << *it << "\n";
}

int main() {

	Automate a = AutomateManager::getAutomateManager().getAutomate(124);

	cout << "automate " << a << endl;

	Etat e(22); e.setCellule(11, true);

	Simulateur s(a, e, 17);

	s.run(25);

	afficherEtModifierEtats(s);

	exit(EXIT_SUCCESS);
}