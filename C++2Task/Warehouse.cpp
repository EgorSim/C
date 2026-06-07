#include "Warehouse.h"
#include <iostream>

void Warehouse::addMaterial(const std::shared_ptr<Material>& material, double amount) {
	stock[material->getName()] += amount;
}

bool Warehouse::takeMaterial(const std::shared_ptr<Material>& material, double amount) {
	std::string name = material->getName();
	if (stock[name] >= amount) {
		stock[name] -= amount;
		return true;
	}
	return false;
}

double Warehouse::getStock(const std::shared_ptr<Material>& material) const {
	auto it = stock.find(material->getName());
	return it != stock.end() ? it->second : 0.0;
}

void Warehouse::printStock() const {
	for (const auto& pair : stock) {
		std::cout << pair.first << ": " << pair.second << "\n";
	}
}