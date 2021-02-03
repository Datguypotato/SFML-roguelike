#pragma once
#include <SFML/Graphics.hpp>

#include "Entity.h"
#include "Collider.h"
#include "Item.h"
#include "WeaponItem.h"

/// <summary>
/// Handels all weapon item functions
/// </summary>
class Weapon
{
public:
	Weapon(int ad, float at);

	void Attack(sf::Vector2f startingPos, sf::Vector2f facingDir);
	void Update(float deltaTime);
	void SetWeapon(Item* item);
	void Draw(sf::RenderWindow& window);

	void OnHit(int dmg);
	void SetAttackBoxPos(sf::Vector2f newPos) { attackbox.setPosition(newPos); }
	Collider GetAttackBox();
	WeaponItem* GetActiveWeapon() { return activeWeapon; }

	void CheckCollision(std::vector<Entity*> enemies);

	bool CanAttack() { return (attackTimer <= 0); }
	void SetBlock(bool b) { activeWeapon->SetBlock(b); }
	bool GetBlock() { return activeWeapon->GetBlock(); }
	void AddAttackDamage(int a) { attackDamage += a; }
	void AddAttackSpeedMultiplier(int percentage);
	std::vector<Entity*>* GetInRange() { return &inRange; }
	int GetRecentDead();
	int GetTargetHits();

private:
	std::vector<Entity*> inRange;
	int recentDead;
	sf::RectangleShape attackbox;

	int targetsHit;
	int baseAttackDamage;
	int attackDamage;
	float attackTimer;
	float baseAttackTimerMax;
	float attackTimerMax;
	float attackSpeedMultiplier; // percentage

	WeaponItem* activeWeapon;
	std::vector<Entity*> weaponProjectiles;

	int timesAttacked;
};