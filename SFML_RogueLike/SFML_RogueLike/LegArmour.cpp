#include "LegArmour.h"

LegArmour::LegArmour()
	:	activeArmour(nullptr)
{
}

void LegArmour::OnHit(std::vector<Entity*> enemies)
{
	for (Entity* enemy : enemies)
	{
		if (activeArmour != nullptr)
			activeArmour->OnHit(enemy);
	}
}

void LegArmour::SetLegArmour(Item* i)
{
	if (activeArmour = dynamic_cast<LegArmourItem*>(i))
	{
		activeArmour = dynamic_cast<LegArmourItem*>(i);
	}
}
