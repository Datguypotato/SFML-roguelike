#include "BluePants.h"

BluePants::BluePants(sf::Texture* itemText, std::string name)
	:	LegArmourItem(itemText, name)
{
}

BluePants::BluePants(sf::Texture* itemText, std::string name, Item* upgrade)
	:	LegArmourItem(itemText, name, upgrade)
{
}

void BluePants::OnLevelEnd(Entity* player)
{
	player->AddMaxHealth(addMaxHealthValue);
	player->Heal(healValue);
}
