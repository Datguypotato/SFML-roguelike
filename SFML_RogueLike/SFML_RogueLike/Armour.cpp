#include "Armour.h"

Armour::Armour(Weapon* w)
	:	armourItem(nullptr),
		weapon(w)
{
}

void Armour::Update(float deltaTime)
{
	if (armourItem != nullptr)
	{
		armourItem->Update(deltaTime);
		SetArmourValue(weapon->GetRecentDead());
	}

}

int Armour::OnHit(int damage, Entity* e, sf::Vector2f playerPos)
{
	if (armourItem != nullptr)
	{
		return armourItem->OnDamaged(damage, e, playerPos);
	}
	else
		return damage;
}

void Armour::OnRoll(Entity* player, sf::Vector2f dir)
{
	if (armourItem != nullptr)
	{
		armourItem->OnRoll(player, dir);
	}
}

void Armour::SetRoll()
{
	if (armourItem != nullptr)
	{
		armourItem->SetRoll();
	}
}

void Armour::UpdateStats(Entity* player)
{
}

void Armour::CheckCollision(std::vector<Entity*> entities)
{
	if (armourItem != nullptr)
		armourItem->CheckCollision(entities);
}

bool Armour::CanRoll()
{
	if (armourItem != nullptr)
	{
		return armourItem->GetCanRollStatus();
	}

	return false;
}

bool Armour::IsRolling()
{
	if (armourItem != nullptr)
	{
		return armourItem->GetIsRollStatus();
	}

	return false;
}

void Armour::SetArmourValue(int value)
{
	if (armourItem != nullptr)
		armourItem->GainShield(value);
	else
		armourValue = value;
}
