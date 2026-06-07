#include "ConstructionSite.h"
#include <algorithm>
#include "iostream"



ConstructionSite::ConstructionSite(const std::string& id, int floors, double totalArea) : id(id), floors(floors), totalArea(totalArea), status(SiteStatus::PLANNED), currentPhaseIndex(0), progressInCurrentPhase(0) {

}

void ConstructionSite::addPhase(const ConstructionPhase& phase) {
	phases.push_back(phase);
}

void ConstructionSite::advanceWork(double laborHourseAvailable) {
	if (status != SiteStatus::IN_PROGRESS) return;
	if (currentPhaseIndex >= phases.size()) {
		status = SiteStatus::COMPLETED;
		return;
	}

	ConstructionPhase& phase = phases[currentPhaseIndex];
	double needed = phase.getRequiredPeople();

	double remaining = needed - progressInCurrentPhase;
	double workDone = std::min(remaining, laborHourseAvailable);

	progressInCurrentPhase += workDone;

	if (progressInCurrentPhase >= needed) {
		currentPhaseIndex++;
		progressInCurrentPhase = 0;
	}

}

void ConstructionSite::start() {
	if (status == SiteStatus::PLANNED || status == SiteStatus::PAUSED) {
		status = SiteStatus::IN_PROGRESS;
		std::cout << "Объект " << id << " начал строительство\n";
	}
}

void ConstructionSite::pause() {
	if (status == SiteStatus::IN_PROGRESS) {
		status = SiteStatus::PAUSED;
		std::cout << "Объект " << id << " приостановлен\n";
	}
}

bool ConstructionSite::isCompleted() {
	return status == SiteStatus::COMPLETED;
}

std::string ConstructionSite::getId() const {
	return id;
}

SiteStatus ConstructionSite::getStatus() const {
	SiteStats stats;
	stats.totalMaterialUsed = totalMaterialUsed;
	stats.totalMoneySpent = totalMoneySpent;
	return status;
}


double ConstructionSite::getCurrentMaterialNeed() const {
	if (currentPhaseIndex >= phases.size()) return 0;
	return phases[currentPhaseIndex].getRequiredAmount();
}

std::shared_ptr<Material> ConstructionSite::getCurrentMaterial() const {
	if (currentPhaseIndex >= phases.size()) return nullptr;
	return phases[currentPhaseIndex].getMaterial();
}

ConstructionSite::SiteStats ConstructionSite::getStats() const {
	SiteStats stats;
	stats.totalMaterialUsed = totalMaterialUsed;
	stats.totalMoneySpent = totalMoneySpent;
	return stats;
}

void ConstructionSite::addMaterialUsage(double amount, double cost) {
	totalMaterialUsed += amount;
	totalMoneySpent += cost;
}