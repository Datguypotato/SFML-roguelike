#include "GreenPants.h"

GreenPants::GreenPants(sf::Texture* itemText, std::string name)
	:	LegArmourItem(itemText, name)
{
	synergy = new Synergy(Synergy::green);
}

GreenPants::GreenPants(sf::Texture* itemText, std::string name, Item* upgrade)
	:	LegArmourItem(itemText, name, upgrade)
{
	synergy = new Synergy(Synergy::green);
}

std::string GreenPants::GetItemStats()
{
	return Item::GetItemStats() + "When Collecting coins received the double the amount\n";
}
