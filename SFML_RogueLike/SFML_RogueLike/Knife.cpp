#include "Knife.h"

Knife::Knife(sf::Texture* itemText, std::string name, SlotRegion* sr)
	:	Item(itemText, name, sr),
		attacks(0)
{
}

Knife::Knife(sf::Texture* itemText, std::string name, SlotRegion* sr, Item* upgrade)
	:	Item(itemText, name, sr, upgrade),
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
	temp += "Attack Damage: " + std::to_string(extraDamage) + "\n";

	return temp;
}
