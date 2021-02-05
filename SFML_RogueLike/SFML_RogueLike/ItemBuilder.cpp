#include "ItemBuilder.h"

ItemBuilder::ItemBuilder()
{
	wb = new WeaponBuilder();
	ab = new ArmourBuilder();
	lab = new LegArmourBuilder();
}

Item* ItemBuilder::BuildRandom()
{
	int random = rand() % 3;
	switch (random)
	{
	case 0:
		return wb->BuildRandom();
		break;
	case 1:
		return ab->BuildRandom();
		break;
	case 2:
		return lab->BuildRandom();
		break;
	default:
		break;
	}

	return nullptr;
}
