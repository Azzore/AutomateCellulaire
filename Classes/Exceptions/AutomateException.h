#pragma once

#include <string>

class AutomateException {
	std::string info;
public:
	AutomateException(const std::string& message) :info(message) {}
	std::string getInfo() const { return info; }
};
