#include "GreenPantsUpgrade.h"

GreenPantsUpgrade::GreenPantsUpgrade(sf::Texture* itemText, std::string name)
	:	GreenPants(itemText, name)
{
	hasFancyPants = true;
}
