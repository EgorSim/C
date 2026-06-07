#include "ConstructionPhase.h"

ConstructionPhase::ConstructionPhase(std::shared_ptr<Material> mat, double area, double customPeopleFactor) : material(mat), area(area), customPeopleFactor(customPeopleFactor) {}

double ConstructionPhase::getRequiredPeople() const {
	if (customPeopleFactor > 0)
		return area * customPeopleFactor;
	return area * material->getPeopleFactor();
}

double ConstructionPhase::getRequiredAmount() const {
	return area;
}

std::shared_ptr<Material> ConstructionPhase::getMaterial() const {
	return material;
}