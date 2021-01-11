#pragma once
#include "Item.h"

class Knife : public Item
{
public:
	Knife(sf::Texture* itemText, std::string name, SlotRegion* sr);
	Knife(sf::Texture* itemText, std::string name, SlotRegion* sr, Item* upgrade);

	Knife* Clone() override { return new Knife(*this); };
	// create upgrade function

	int OnAttack(Entity* entity) override;
	std::string GetItemStats() override;
	

protected:
	int attacks;
	int extraDamage = 3;
};

