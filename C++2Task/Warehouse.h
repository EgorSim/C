#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <unordered_map>
#include <string>
#include "Material.h"
#include <memory>

class Warehouse {
private:
	std::unordered_map  <std::string, double > stock;

public:
	void addMaterial(const std::shared_ptr<Material>& material, double amount);
	bool takeMaterial(const std::shared_ptr<Material>& material, double amount);
	double getStock(const std::shared_ptr<Material>& material) const;
	void printStock() const;
};

#endif