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

/// <summary>
/// When Entity damage the player
/// </summary>
/// <param name="damage"></param>
/// <param name="e"></param>
/// <param name="playerPos"></param>
/// <returns></returns>
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

void Armour::SetArmour(Item* item)
{
	if (item == nullptr)
		return;

	if (WeaponItem* w = dynamic_cast<WeaponItem*>(item))
	{
		armourItem = static_cast<ArmourItem*>(item);
	}
	else
		armourItem = nullptr;
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
