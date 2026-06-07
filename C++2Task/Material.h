#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>

class Material {
private:
	std::string name;
	double costPerUnit;
	double peopleFactor;


public:
	Material(const std::string& name, double costPerUnit, double peopleFactor);


	std::string getName() const;
	double getCost() const;
	double getPeopleFactor() const;

	void updateCost(double newCost);
};
#endif