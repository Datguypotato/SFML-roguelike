#include "GreenPants.h"

GreenPants::GreenPants(sf::Texture* itemText, std::string name)
	:	LegArmourItem(itemText, name)
{
}

GreenPants::GreenPants(sf::Texture* itemText, std::string name, Item* upgrade)
	:	LegArmourItem(itemText, name, upgrade)
{
}
