#pragma once
#include <vector>

#include "Collectable.h"
#include "Animation.h"
#include "Player.h"

#include "Knife.h"
#include "BloodKnife.h"

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

private:
	std::vector<Collectable*> loots;
};
