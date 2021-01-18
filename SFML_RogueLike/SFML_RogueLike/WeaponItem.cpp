#include "WeaponItem.h"

WeaponItem::WeaponItem(sf::Texture* itemText, std::string name)
	:	Item(itemText, name, new SlotRegion(SlotRegion::Weapon)),
		isBlocking(false),
		isEmpowered(false)
{
}

WeaponItem::WeaponItem(sf::Texture* itemText, std::string name, Item* upgrade)
	:	Item(itemText, name, new SlotRegion(SlotRegion::Weapon), upgrade),
		isBlocking(false),
		isEmpowered(false)
{
}

std::string WeaponItem::GetItemStats()
{
	return "Type: Weapon\n";
}

void WeaponItem::Draw(sf::RenderWindow& window)
{
	Item::Draw(window);
}
