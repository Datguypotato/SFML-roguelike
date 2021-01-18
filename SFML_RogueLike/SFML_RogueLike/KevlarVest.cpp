#include "KevlarVest.h"

KevlarVest::KevlarVest(sf::Texture* itemText, std::string name)
	:	ArmourItem(itemText, name)
{
}

KevlarVest::KevlarVest(sf::Texture* itemText, std::string name, Item* upgrade)
	: ArmourItem(itemText, name, upgrade)
{
}

int KevlarVest::OnDamaged(int damage, Entity* e, sf::Vector2f playerPos)
{
	if (shieldAmount > 0)
	{
		if (damage - shieldAmount >= 0)
		{
			damage -= shieldAmount;
			shieldAmount = 0;
			OnExplodeShield(playerPos);
		}
		else
		{
			shieldAmount -= damage;
			damage = 0;
		}
	}
	return damage;
}

void KevlarVest::GainShield(int amount)
{
	shieldAmount += amount * shieldGainPerKill;
}
