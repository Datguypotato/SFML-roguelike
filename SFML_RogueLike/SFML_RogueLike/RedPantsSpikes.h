#pragma once
#include "RedPants.h"

class RedPantsSpikes : public RedPants
{
public:
	RedPantsSpikes(sf::Texture* itemText, std::string name);

	RedPantsSpikes* Clone() { return new RedPantsSpikes(*this); }
};

