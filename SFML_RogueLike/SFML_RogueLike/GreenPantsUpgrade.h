#pragma once
#include "GreenPants.h"

class GreenPantsUpgrade : public GreenPants
{
public:
	GreenPantsUpgrade(sf::Texture* itemText, std::string name);

	GreenPantsUpgrade* Clone() { return new GreenPantsUpgrade(*this); }
};

