#include "CompanyUp.h"
#include <iostream>

ConstructionCompany::ConstructionCompany(std::unique_ptr<Strategy> strategy)
    : procurementStrategy(std::move(strategy)), currentWeek(0), totalMoneySpent(0) {
}

void ConstructionCompany::addSite(std::unique_ptr<ConstructionSite> site) {
    sites.push_back(std::move(site));
}

void ConstructionCompany::setStrategy(std::unique_ptr<Strategy> strategy) {
    procurementStrategy = std::move(strategy);
}


void ConstructionCompany::registerMaterial(std::shared_ptr<Material> material) {
    allMaterials.push_back(material);
}

void ConstructionCompany::updateMaterialPrices() {
    double inflationRate = 1.02;
    for (auto& material : allMaterials) {
        double newCost = material->getCost() * inflationRate;
        material->updateCost(newCost);
        std::cout << "  Цена на " << material->getName()
            << " выросла до " << newCost << " руб.\n";
    }
}

void ConstructionCompany::pauseSite(const std::string& siteId) {
    for (auto& site : sites) {
        if (site->getId() == siteId) {
            site->pause();
            std::cout << "Объект " << siteId << " ПРИОСТАНОВЛЕН\n";
            return;
        }
    }
    std::cout << "Объект " << siteId << " не найден\n";
}

void ConstructionCompany::resumeSite(const std::string& siteId) {
    for (auto& site : sites) {
        if (site->getId() == siteId) {
            site->start();  // start() возобновляет работу (если статус PAUSED)
            std::cout << "Объект " << siteId << " ВОЗОБНОВЛЁН\n";
            return;
        }
    }
    std::cout << "Объект " << siteId << " не найден\n";
}

void ConstructionCompany::simulateWeek() {
    currentWeek++;
    std::cout << "\n=== Неделя " << currentWeek << " ===\n";

    updateMaterialPrices();

    //  Обрабатываем каждый объект
    for (auto& site : sites) {
        if (site->isCompleted()) continue;

        if (site->getStatus() != SiteStatus::IN_PROGRESS) {
            std::cout << "Объект " << site->getId() << " не в работе (статус: ";
            if (site->getStatus() == SiteStatus::PLANNED) std::cout << "PLANNED";
            else if (site->getStatus() == SiteStatus::PAUSED) std::cout << "PAUSED";
            std::cout << ")\n";
            continue;
        }

        auto material = site->getCurrentMaterial();
        if (!material) {
            continue;
        }

        double needed = site->getCurrentMaterialNeed();
        if (needed <= 0) continue;

        double currentStock = warehouse.getStock(material);

        double toOrder = procurementStrategy->calculateOrderAmount(needed, currentStock);

        if (toOrder > 0) {
            double cost = material->getCost() * toOrder;
            totalMoneySpent += cost;
            warehouse.addMaterial(material, toOrder);

            std::cout << "  Закуплено " << toOrder << " " << material->getName()
                << " на " << cost << " руб.\n";
        }

        double available = warehouse.getStock(material);

        if (available >= needed) {
            warehouse.takeMaterial(material, needed);

            
            double materialCost = needed * material->getCost();
            site->addMaterialUsage(needed, materialCost);
          

            std::cout << "  Выдано " << needed << " " << material->getName()
                << " на объект " << site->getId() << "\n";
        }
    }

    double weeklyLabor = 1000.0;  

    std::cout << "\n--- Выполнение работ ---\n";
    for (auto& site : sites) {
        if (site->getStatus() == SiteStatus::IN_PROGRESS) {
            site->advanceWork(weeklyLabor);

            auto material = site->getCurrentMaterial();
            if (material) {
                std::cout << "  " << site->getId() << ": строится, нужно "
                    << site->getCurrentMaterialNeed() << " " << material->getName() << "\n";
            }
            else {
                if (site->isCompleted()) {
                    std::cout << "  " << site->getId() << ": ЗАВЕРШЁН!\n";
                }
            }
        }
        else if (site->isCompleted()) {
            std::cout << "  " << site->getId() << ": уже завершён\n";
        }
    }

    std::cout << "\n--- Остатки на складе ---\n";
    warehouse.printStock();
}



void ConstructionCompany::printStatistics() const {
    std::cout << "\n=== STATISTICS ===\n";
    std::cout << "Total weeks: " << currentWeek << "\n";
    std::cout << "Total money spent: " << totalMoneySpent << "\n\n";

    for (const auto& site : sites) {
        auto stats = site->getStats();
        std::cout << "Site: " << site->getId() << "\n";
        std::cout << "  Status: ";
        switch (site->getStatus()) {
        case SiteStatus::PLANNED: std::cout << "Planned\n"; break;
        case SiteStatus::IN_PROGRESS: std::cout << "In progress\n"; break;
        case SiteStatus::PAUSED: std::cout << "Paused\n"; break;
        case SiteStatus::COMPLETED: std::cout << "Completed\n"; break;
        }
        std::cout << "  Materials used: " << stats.totalMaterialUsed << "\n";
        std::cout << "  Money spent: " << stats.totalMoneySpent << " rub.\n\n";
    }
}

bool ConstructionCompany::allSitesCompleted() const {
    for (const auto& site : sites) {
        if (!site->isCompleted()) return false;
    }
    return true;
}