#include "RedPants.h"

RedPants::RedPants(sf::Texture* itemText, std::string name)
	:	LegArmourItem(itemText, name)
{
}

RedPants::RedPants(sf::Texture* itemText, std::string name, Item* upgrade)
	:	LegArmourItem(itemText, name, upgrade)
{
}

void RedPants::OnHit(Entity* enemy)
{
	if (rand() % 100 < stunPercentage)
		enemy->GetEffectHandler()->SetStunned(stunTime);
}
