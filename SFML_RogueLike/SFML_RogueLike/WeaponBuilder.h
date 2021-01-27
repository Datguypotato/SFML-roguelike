#pragma once
#include <iostream>

#include "Collectable.h"

#include "Knife.h"
#include "BloodKnife.h"
#include "FanSword.h"
#include "WindSlasher.h"

#include "Shield.h"
#include "ShieldSword.h"

class WeaponBuilder
{
public:
	WeaponBuilder();

	void BuildWeapon(int id, sf::Vector2f position);

	Collectable* BuildKnife(sf::Vector2f pos);
	Collectable* BuildUpgradeKnife(sf::Vector2f pos);
	Item* UpgradeKnife();

	Collectable* BuildFanSword(sf::Vector2f pos);
	Item* UpgradeFanSword();

	Collectable* BuildShield(sf::Vector2f pos);
	Item* UpgradeShield();

	std::vector<Collectable*> GetLoot() { return loots; }

private:
	sf::Texture* LoadTexture(std::string path);

	std::vector<Collectable*> loots;
};

