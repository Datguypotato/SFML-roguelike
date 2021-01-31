#pragma once
#include "Entity.h"
#include "LegArmourItem.h"

class LegArmour
{
public:
	LegArmour();

	void OnHit(std::vector<Entity*> enemy);
	void OnCollectCoins() {}
	void SetNewMaxHp(Entity* player) {}

	LegArmourItem* GetActiveLegArmour() { return activeArmour; }

	void SetLegArmour(Item* i);

protected:
	LegArmourItem* activeArmour;
};

