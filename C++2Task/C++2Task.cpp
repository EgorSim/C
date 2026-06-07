#include <memory>
#include "CompanyUp.h"
#include "ConstructionPhase.h"
#include "ConstructionSite.h"
#include "Material.h"
#include <windows.h> 
int main() {
    SetConsoleOutputCP(CP_UTF8);  
    

    auto brick = std::make_shared<Material>("Brick", 12.5, 0.5);
    auto concrete = std::make_shared<Material>("Concrete", 8.0, 0.3);
    auto wood = std::make_shared<Material>("Wood", 5.0, 0.8); 

    auto site1 = std::make_unique<ConstructionSite>("TC Aurora", 3, 1500.0);
    site1->addPhase(ConstructionPhase(brick, 800.0));
    site1->addPhase(ConstructionPhase(concrete, 700.0));
    site1->start();

    
    auto site2 = std::make_unique<ConstructionSite>("JK Solnechny", 5, 2500.0);
    site2->addPhase(ConstructionPhase(brick, 1200.0));
    site2->addPhase(ConstructionPhase(concrete, 1000.0));
    site2->addPhase(ConstructionPhase(wood, 500.0));
    site2->start();

    auto site3 = std::make_unique<ConstructionSite>("Office Center", 8, 4000.0);
    site3->addPhase(ConstructionPhase(concrete, 2000.0));
    site3->addPhase(ConstructionPhase(brick, 1500.0));
    site3->start();
    auto company = std::make_unique<ConstructionCompany>(std::make_unique<ModerateBufferStrategy>());

    company->registerMaterial(brick);
    company->registerMaterial(concrete);
    company->registerMaterial(wood);

    company->addSite(std::move(site1));
    company->addSite(std::move(site2));
    company->addSite(std::move(site3));

    bool thirdSiteStarted = false;

    while (!company->allSitesCompleted()) {
        company->simulateWeek();

        if (company->getCurrentWeek() == 3 && !thirdSiteStarted) {
            company->resumeSite("Офисный центр");  
            thirdSiteStarted = true;
        }

    }

    company->printStatistics();

    return 0;
}