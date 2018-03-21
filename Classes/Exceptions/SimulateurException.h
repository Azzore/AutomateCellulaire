#pragma once

#include <string>

class SimulateurException {
	std::string info;
public:
	SimulateurException(const std::string& message) :info(message) {}
	std::string getInfo() const { return info; }
};