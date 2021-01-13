#include "Shield.h"

Shield::Shield(sf::Texture* itemText, std::string name)
	:	WeaponItem(itemText, name)
{
}

Shield::Shield(sf::Texture* itemText, std::string name, Item* upgrade)
	:	WeaponItem(itemText, name, upgrade)
{
}

void Shield::OnAttack(sf::Vector2f startingPos, sf::Vector2f direction)
{
	SetShield(true);
}

void Shield::UnShield()
{
	SetShield(false);
}
