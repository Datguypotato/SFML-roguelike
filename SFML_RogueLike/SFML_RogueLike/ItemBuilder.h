#pragma once
#include "WeaponBuilder.h"
#include "ArmourBuilder.h"
#include "LegArmourBuilder.h"

class ItemBuilder
{
public:
	ItemBuilder();

	Item* BuildRandom();

private:
	WeaponBuilder* wb;
	ArmourBuilder* ab;
	LegArmourBuilder* lab;
};

