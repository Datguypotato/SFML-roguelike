#include "ArmourItem.h"

ArmourItem::ArmourItem(sf::Texture* itemText, std::string name)
	:	Item(itemText, name, new SlotRegion(SlotRegion::body))
{
}

ArmourItem::ArmourItem(sf::Texture* itemText, std::string name, Item* upgrade)
	:	Item(itemText, name, new SlotRegion(SlotRegion::body), upgrade)
{
}
