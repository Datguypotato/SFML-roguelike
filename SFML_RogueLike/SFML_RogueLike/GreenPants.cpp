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
