#pragma once
#include "Item.h"

class LegArmourItem : public Item
{
public:
	LegArmourItem(sf::Texture* itemText, std::string name);
	LegArmourItem(sf::Texture* itemText, std::string name, Item* upgrade);

	virtual LegArmourItem* Clone() { return new LegArmourItem(*this); }

	virtual void OnHit(Entity* enemy) {}
	virtual int OnCollect(int coins) { return coins; }
	virtual void OnLevelEnd(Entity* player) {}

	bool hasFancyPants = false;
};