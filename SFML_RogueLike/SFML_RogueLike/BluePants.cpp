#include "BluePants.h"

BluePants::BluePants(sf::Texture* itemText, std::string name)
	:	LegArmourItem(itemText, name)
{
	synergy = new Synergy(Synergy::blue);
}

BluePants::BluePants(sf::Texture* itemText, std::string name, Item* upgrade)
	:	LegArmourItem(itemText, name, upgrade)
{
	synergy = new Synergy(Synergy::blue);
}

void BluePants::OnLevelEnd(Entity* player)
{
	player->AddMaxHealth(addMaxHealthValue);
	player->Heal(healValue);
}

std::string BluePants::GetItemStats()
{
	return Item::GetItemStats() + "At the end of every level receive " + std::to_string(addMaxHealthValue) + " health\n";
}
