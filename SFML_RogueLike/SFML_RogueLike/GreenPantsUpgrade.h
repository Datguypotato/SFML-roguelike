#pragma once
#include "GreenPants.h"

class GreenPantsUpgrade : public GreenPants
{
public:
	GreenPantsUpgrade(sf::Texture* itemText, std::string name);

	GreenPantsUpgrade* Clone() { return new GreenPantsUpgrade(*this); }

	std::string GetItemStats() { return GreenPants::GetItemStats() + "Receive 10% discount in shop\n"; }
};

