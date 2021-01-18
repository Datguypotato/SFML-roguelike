#pragma once

#include "Collectable.h"
#include "RedShirt.h"
#include "RedSpikes.h"

#include "ThiefRobe.h"
#include "MagicRobe.h"

#include "KevlarVest.h"
#include "PlatedArmour.h"

class ArmourBuilder
{
public:
	ArmourBuilder();

	Collectable* BuildRedShirt(sf::Vector2f pos);
	Item* BuildRedShirtUpgrade();

	Collectable* BuildThiefRobe(sf::Vector2f pos);
	Item* BuildUpgradeThiefRobe();

	Collectable* BuildKevlarVest(sf::Vector2f pos);
	Item* BuildUpgradeKevelarVest();


	std::vector<Collectable*> GetLoot() { return loots; }

private:
	sf::Texture* LoadTexture(std::string path);

	std::vector<Collectable*> loots;
};

