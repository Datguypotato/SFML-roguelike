#include "Shield.h"

Shield::Shield(sf::Texture* itemText, std::string name)
	:	WeaponItem(itemText, name)
{
	attackDamage = 5;
}

Shield::Shield(sf::Texture* itemText, std::string name, Item* upgrade)
	:	WeaponItem(itemText, name, upgrade)
{
}

void Shield::OnAttack(sf::Vector2f startingPos, sf::Vector2f direction)
{
	SetBlock(true);
}

int Shield::OnHit(Entity* entity)
{
	entity->GetEffectHandler()->SetStunned(stunTime);
	return 0;
}

std::string Shield::GetItemStats()
{
	std::string temp = WeaponItem::GetItemStats();
	temp += "When attack is on cooldown you block\nWhen blocking enemies deal half their damage to you\n";
	return temp;
}

void Shield::UnShield()
{
	SetBlock(false);
}
