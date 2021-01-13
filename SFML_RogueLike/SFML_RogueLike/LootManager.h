#pragma once
#include <vector>

#include "Collectable.h"
#include "Animation.h"
#include "Player.h"

#include "Knife.h"
#include "BloodKnife.h"
#include "FanSword.h"
#include "WindSlasher.h"

#include "Shield.h"
#include "ShieldSword.h"

class LootManager
{
public:
	LootManager();

	void Update(float deltaTime);
	void CheckTrigger(Player* p);

	void Draw(sf::RenderWindow& window);

	Item* GetRandomLoot();

	Collectable* BuildKnife(sf::Vector2f pos);
	Collectable* BuildUpgradeKnife(sf::Vector2f pos);
	Item* UpgradeKnife();

	Collectable* BuildFanSword(sf::Vector2f pos);
	Item* UpgradeFanSword();

	Collectable* BuildShield(sf::Vector2f pos);
	Item* UpgradeShield();

private:
	sf::Texture* LoadTexture(std::string path);
	std::vector<Collectable*> loots;
};
