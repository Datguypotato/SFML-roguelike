#include "ShieldSword.h"

ShieldSword::ShieldSword(sf::Texture* itemText, std::string name)
	:	Shield(itemText, name)
{
}

int ShieldSword::OnHit(Entity* entity)
{
	if (isEmpowered)
		return entity->GetAttackDamage() / 2;
	else
		return 0;
}