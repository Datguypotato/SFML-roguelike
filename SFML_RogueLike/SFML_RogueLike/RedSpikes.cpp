#include "RedSpikes.h"

RedSpikes::RedSpikes(sf::Texture* itemText, std::string name)
	:	RedShirt(itemText, name)
{
}

int RedSpikes::OnDamaged(int damage, Entity* e, sf::Vector2f playerPos)
{
	if (isProtected)
		e->OnHit(damage);

	return RedShirt::OnDamaged(damage, e, playerPos);
}
