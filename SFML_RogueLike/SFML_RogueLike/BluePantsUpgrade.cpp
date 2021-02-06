#include "BluePantsUpgrade.h"

BluePantsUpgrade::BluePantsUpgrade(sf::Texture* itemText, std::string name)
	:	BluePants(itemText, name)
{
	healValue = 10;
}

std::string BluePantsUpgrade::GetItemStats()
{
	return BluePants::GetItemStats() + "Now also heal " + std::to_string(healValue) + " health\n";
}
