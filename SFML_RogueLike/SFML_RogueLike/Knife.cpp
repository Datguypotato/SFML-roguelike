#include "Knife.h"

Knife::Knife(sf::Texture* itemText, std::string name)
	:	WeaponItem(itemText, name),
		attacks(0)
{
	attackDamage = 0;
	minusAttackTimerMax = 0.5f;
}

Knife::Knife(sf::Texture* itemText, std::string name, Item* upgrade)
	:	WeaponItem(itemText, name, upgrade),
		attacks(0)
{
}

int Knife::OnHit(Entity* entity)
{
	attacks++;

	if (attacks % 3 == 0)
	{
		return extraDamage;
	}
	return 0;
}

std::string Knife::GetItemStats()
{
	std::string temp = Item::GetItemStats();
	temp += "*Every third hit will deal " + std::to_string(extraDamage) + "extra damage\n";

	return temp;
}
