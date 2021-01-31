#pragma once
#include "Collectable.h"
#include "RedPants.h"
#include "RedPantsSpikes.h"
#include "GreenPants.h"
#include "GreenPantsUpgrade.h"
#include "BluePants.h"
#include "BluePantsUpgrade.h"

class LegArmourBuilder
{
public:
	LegArmourBuilder();

	Collectable* BuildLegArmour(int ID, sf::Vector2f position);

	Collectable* BuildRedPants(sf::Vector2f position);
	Item* BuildUpgradeRedPants();

	Collectable* BuildGreenPants(sf::Vector2f position);
	Item* BuildUpgradeGreenPants();

	Collectable* BuildBluePants(sf::Vector2f position);
	Item* BuildUpgradeBluePants();

	std::vector<Collectable*> GetLoot() { return loot; }

protected:
	sf::Texture* Loadtexture(std::string path);


	std::vector<Collectable*> loot;
};