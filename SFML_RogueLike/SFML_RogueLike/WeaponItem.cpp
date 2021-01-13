#include "WeaponItem.h"

WeaponItem::WeaponItem(sf::Texture* itemText, std::string name)
	:	Item(itemText, name, new SlotRegion(SlotRegion::Weapon)),
		isShielded(false),
		isEmpowered(false)
{
}

WeaponItem::WeaponItem(sf::Texture* itemText, std::string name, Item* upgrade)
	:	Item(itemText, name, new SlotRegion(SlotRegion::Weapon), upgrade),
		isShielded(false),
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
