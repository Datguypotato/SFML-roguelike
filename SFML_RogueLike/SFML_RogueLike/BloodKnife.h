#pragma once
#include "Knife.h"

class BloodKnife : public Knife
{
public:
	BloodKnife(sf::Texture* itemText, std::string name, SlotRegion* sr);

	BloodKnife* Clone() override { return new BloodKnife(*this); }
	int OnHit(Entity* entity) override;
	std::string GetItemStats() override;

private:
	int bleedTimes = 5;
	int bleedDamage = 1;
};

