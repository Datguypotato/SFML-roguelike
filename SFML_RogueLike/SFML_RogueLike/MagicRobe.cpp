#include "MagicRobe.h"

MagicRobe::MagicRobe(sf::Texture* itemText, std::string name)
	:	ThiefRobe(itemText, name)
{
}

void MagicRobe::OnRoll(Entity* player, sf::Vector2f dir)
{
	ThiefRobe::OnRoll(player, dir);

	if (!IsRolling)
		isProtected = false;
}

void MagicRobe::SetRoll()
{
	ThiefRobe::SetRoll();

	if (CanRoll)
		isProtected = true;
}

int MagicRobe::OnDamaged(int damage, Entity* e, sf::Vector2f playerPos)
{
	if (isProtected)
		return 0;
	else
		return damage;
}

std::string MagicRobe::GetItemStats()
{
	return ThiefRobe::GetItemStats() + "When rolling you cannot receive damage\n";
}
