#ifndef CONSTRUCTION_PHASE_H
#define CONSTRUCTION_PHASE_H



#include <memory>
#include "Material.h"
class ConstructionPhase {
private:
	std::shared_ptr<Material> material;
	double area;
	double customPeopleFactor;

public:
	ConstructionPhase(std::shared_ptr<Material> mat, double area, double customPeopleFactor = 0.0);

	double getRequiredPeople() const;
	double getRequiredAmount() const;
	std::shared_ptr<Material> getMaterial() const;
};

#endif 
