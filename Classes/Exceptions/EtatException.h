#pragma once

#include <string>

class EtatException {
	std::string info;
public:
	EtatException(const std::string& message) :info(message) {}
	std::string getInfo() const { return info; }
};
