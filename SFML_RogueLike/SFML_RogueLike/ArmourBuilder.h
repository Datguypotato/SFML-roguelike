#pragma once
#include <iostream>

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

	Collectable* BuildArmour(int ID, sf::Vector2f position);

	Collectable* BuildRedShirt(sf::Vector2f pos);
	Collectable* BuildThiefRobe(sf::Vector2f pos);
	Collectable* BuildKevlarVest(sf::Vector2f pos);

	std::vector<Collectable*> GetLoot() { return loots; }

private:
	Item* BuildRedShirtUpgrade();
	Item* BuildUpgradeThiefRobe();
	Item* BuildUpgradeKevelarVest();

	sf::Texture* LoadTexture(std::string path);

	std::vector<Collectable*> loots;
};

