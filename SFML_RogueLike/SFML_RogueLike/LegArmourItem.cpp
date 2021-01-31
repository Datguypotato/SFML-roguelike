#include "LegArmourItem.h"

LegArmourItem::LegArmourItem(sf::Texture* itemText, std::string name)
	:	Item(itemText, name, new SlotRegion(SlotRegion::legs))
{
}

LegArmourItem::LegArmourItem(sf::Texture* itemText, std::string name, Item* upgrade)
	:	Item(itemText, name, new SlotRegion(SlotRegion::legs), upgrade)
{
}
