#ifndef CONSTRUCTION_SITE_H
#define CONSTRUCTION_SITE_H

#include <string>
#include <vector>
#include <memory>
#include "ConstructionPhase.h"

enum class SiteStatus {
    PLANNED,
    IN_PROGRESS,
    PAUSED,
    COMPLETED
};


class ConstructionSite {
private:
    std::string id;
    int floors;
    double totalArea;
    SiteStatus status;
    std::vector<ConstructionPhase> phases;
    size_t currentPhaseIndex;        
    double progressInCurrentPhase;
    double totalMaterialUsed = 0;
    double totalMoneySpent = 0;

public:
    ConstructionSite(const std::string& id, int floors, double totalArea);

    void addPhase(const ConstructionPhase& phase);
    void addMaterialUsage(double amount, double cost);

    void start();
    void pause();

    bool isCompleted();
    std::string getId() const;
    SiteStatus getStatus() const;     

    void advanceWork(double laborHoursAvailable);  

    double getCurrentMaterialNeed() const;
    std::shared_ptr<Material> getCurrentMaterial() const;

    struct SiteStats {                 
        double totalMaterialUsed = 0;
        double totalMoneySpent = 0;
    };
    SiteStats getStats() const;
};

#endif
