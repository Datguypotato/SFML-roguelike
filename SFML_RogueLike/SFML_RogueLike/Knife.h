#pragma once
#include "WeaponItem.h"

class Knife : public WeaponItem
{
public:
	Knife(sf::Texture* itemText, std::string name);
	Knife(sf::Texture* itemText, std::string name, Item* upgrade);

	Knife* Clone() override { return new Knife(*this); };

	int OnHit(Entity* entity) override;
	std::string GetItemStats() override;
	

protected:
	int attacks;
	int extraDamage = 3;
};

