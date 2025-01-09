#pragma once
#include <string>
#include <iostream>
class Island {
public:
	Island(const std::string& name, const std::string& description)
		: name(name), description(description) {}

	const std::string& getName() const { return name; }
	const std::string& getDescription() const { return description; }

private:
	std::string name;
	std::string description;
};