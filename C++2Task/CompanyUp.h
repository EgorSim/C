#ifndef COMPANY_UP_H
#define COMPANY_UP_H
#include <vector>
#include <memory>
#include "ConstructionSite.h"
#include "Warehouse.h"
#include "Strategy.h"


class ConstructionCompany {
private:
	std::vector<std::shared_ptr<Material>> allMaterials;
	std::vector<std::unique_ptr<ConstructionSite>> sites;
	Warehouse warehouse;
	std::unique_ptr<Strategy> procurementStrategy;
	int currentWeek;
	double totalMoneySpent;

	

public:
	void updateMaterialPrices();
	void registerMaterial(std::shared_ptr<Material> material);
	ConstructionCompany(std::unique_ptr<Strategy> strategy);
	void addSite(std::unique_ptr<ConstructionSite> site);
	void setStrategy(std::unique_ptr<Strategy> strategy);

	void simulateWeek(); 
	int getCurrentWeek() const { return currentWeek; }

	void printStatistics() const;

	bool allSitesCompleted() const;

	void pauseSite(const std::string& siteId);
	void resumeSite(const std::string& siteId);

};
#endif