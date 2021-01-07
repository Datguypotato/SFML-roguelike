#pragma once
#include <vector>

#include "Item.h"

class LootManager
{
public:
	LootManager();

	Item* GetRandomLoot();

private:
	std::vector<Item*> loots;
};

