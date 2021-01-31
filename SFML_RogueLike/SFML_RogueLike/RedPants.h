#pragma once
#include "LegArmourItem.h"

class RedPants : public LegArmourItem
{
public:
	RedPants(sf::Texture* itemText, std::string name);
	RedPants(sf::Texture* itemText, std::string name, Item* upgrade);

	RedPants* Clone() { return new RedPants(*this); }

	void OnHit(Entity* enemy) override;

protected:
	int stunPercentage = 25;
	int stunTime = 1;
};

