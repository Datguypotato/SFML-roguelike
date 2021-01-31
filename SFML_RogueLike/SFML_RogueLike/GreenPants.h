#pragma once
#include "LegArmourItem.h"

class GreenPants : public LegArmourItem
{
public:
	GreenPants(sf::Texture* itemText, std::string name);
	GreenPants(sf::Texture* itemText, std::string name, Item* upgrade);

	GreenPants* Clone() { return new GreenPants(*this); }

	int OnCollect(int coins) { return coins * multiplier; }

protected:
	int multiplier = 2;
};

