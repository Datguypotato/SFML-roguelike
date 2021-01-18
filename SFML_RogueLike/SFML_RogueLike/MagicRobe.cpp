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
