#include "AutomateManager.h"

AutomateManager* AutomateManager::instance = nullptr;

AutomateManager::AutomateManager() {
	for (int i = 0; i < 256; ++i) {
		automates[i] = nullptr;
	}
}

AutomateManager & AutomateManager::getAutomateManager() {

	if (instance == nullptr) {
		instance = new AutomateManager;
	}
	return *instance;
}

AutomateManager::~AutomateManager() {
	for (int i = 0; i < 256; ++i) {
		delete automates[i];
	}
}

void AutomateManager::freeAutomateManager() {
	delete instance;
	instance = nullptr;
}

const Automate& AutomateManager::getAutomate(unsigned int i) {
	if (automates[i] == nullptr) {
		automates[i] = new Automate(i);
	}
	return *automates[i];
}

const Automate& AutomateManager::getAutomate(std::string chaine) {
	unsigned int n = NumBitToNum(chaine);
	return getAutomate(n);
}