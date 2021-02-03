#pragma once
#include "Entity.h"
#include "ArmourItem.h"
#include "Weapon.h"

/// <summary>
/// Handels all armour item functions
/// </summary>
class Armour
{
public:
	Armour(Weapon* w);

	void Update(float deltaTime);
	int OnHit(int damage, Entity* e, sf::Vector2f playerPos);
	void OnRoll(Entity* player, sf::Vector2f dir);
	void SetRoll();
	void UpdateStats(Entity* player);
	void CheckCollision(std::vector<Entity*> entities);

	virtual void Draw(sf::RenderWindow& window) {}

	void SetArmour(Item* aItem) { armourItem = static_cast<ArmourItem*>(aItem); }
	ArmourItem* GetActiveArmour() { return armourItem; }

	bool CanRoll();
	bool IsRolling();
	void SetArmourValue(int value);

protected:
	ArmourItem* armourItem;
	Weapon* weapon;

	int armourValue = 0;
};

