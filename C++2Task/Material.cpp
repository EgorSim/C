#include "Material.h"

Material::Material(const std::string& name, double costPerUnit, double peopleFactor) : name(name), costPerUnit(costPerUnit), peopleFactor(peopleFactor) {
}

std::string Material::getName() const { return name; }
double Material::getCost() const { return costPerUnit; }
double Material::getPeopleFactor() const { return peopleFactor; }
void Material::updateCost(double newCost) { costPerUnit = newCost; }