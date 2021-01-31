#pragma once
#include "Collectable.h"
#include "RedPants.h"
#include "RedPantsSpikes.h"

class LegArmourBuilder
{
public:
	LegArmourBuilder();

	Collectable* BuildLegArmour(int ID, sf::Vector2f position);

	Collectable* BuildRedPants(sf::Vector2f position);
	Item* BuildUpgradePants();

	Collectable* BuildGreenPants(sf::Vector2f position);

	std::vector<Collectable*> GetLoot() { return loot; }

protected:
	sf::Texture* Loadtexture(std::string path);


	std::vector<Collectable*> loot;
};