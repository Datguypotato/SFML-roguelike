#include "RedShirt.h"

RedShirt::RedShirt(sf::Texture* itemText, std::string name)
	:	ArmourItem(itemText, name),
		timer(3.0f),
		maxTimer(timer)
{
	synergy = new Synergy(Synergy::red);
}

RedShirt::RedShirt(sf::Texture* itemText, std::string name, Item* upgrade)
	:	ArmourItem(itemText, name, upgrade),
		timer(3.0f),
		maxTimer(timer)
{
	synergy = new Synergy(Synergy::red);
}

void RedShirt::Update(float deltaTime)
{
	timer -= deltaTime;

	if (timer <= 0)
	{
		isProtected = true;
		timer = maxTimer;
	}
}

int RedShirt::OnDamaged(int damage, Entity* e, sf::Vector2f playerPos)
{
	if (isProtected)
	{
		isProtected = false;
		return 0;
	}
	else
		return damage;
}
