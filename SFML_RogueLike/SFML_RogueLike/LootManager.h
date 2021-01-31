#pragma once
#include <vector>

#include "WeaponBuilder.h"
#include "ArmourBuilder.h"
#include "LegArmourBuilder.h"

class LootManager
{
public:
	LootManager();

	void Update(float deltaTime);
	void CheckTrigger(Player* p);

	void Draw(sf::RenderWindow& window);

	Item* GetRandomLoot();
	WeaponBuilder* GetWeaponb() { return weaponb; }
	ArmourBuilder* GetArmourb() { return armourb; }
	LegArmourBuilder* GetLegArmourb() { return legArmourb; }

private:
	std::vector<Collectable*> Getloots();

	WeaponBuilder* weaponb;
	ArmourBuilder* armourb;
	LegArmourBuilder* legArmourb;
};
