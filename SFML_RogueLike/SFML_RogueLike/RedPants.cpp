#include "RedPants.h"

RedPants::RedPants(sf::Texture* itemText, std::string name)
	:	LegArmourItem(itemText, name)
{
	synergy = new Synergy(Synergy::red);
}

RedPants::RedPants(sf::Texture* itemText, std::string name, Item* upgrade)
	:	LegArmourItem(itemText, name, upgrade)
{
	synergy = new Synergy(Synergy::red);
}

void RedPants::OnHit(Entity* enemy)
{
	if (rand() % 100 < stunPercentage)
		enemy->GetEffectHandler()->SetStunned(stunTime);
}
