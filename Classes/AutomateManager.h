#pragma once

#include <string>

#include "Automate.h"

class AutomateManager {

	static AutomateManager* instance;
	Automate* automates[256];

	//Constructeurs
	AutomateManager();
	~AutomateManager();


public:
	static AutomateManager & getAutomateManager();
	static void freeAutomateManager();
	const Automate& getAutomate(unsigned int);
	const Automate& getAutomate(std::string);

};