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

void LegArmour::SetLegArmour(Item* item)
{
	if (item == nullptr)
		return;

	if (LegArmourItem* l = dynamic_cast<LegArmourItem*>(item))
	{
		activeArmour = static_cast<LegArmourItem*>(item);
	}
	else
		activeArmour = nullptr;
}