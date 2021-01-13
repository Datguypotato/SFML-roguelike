#pragma once
#include <SFML/Graphics.hpp>

#include "Entity.h"
#include "Collider.h"
#include "Item.h"
#include "WeaponItem.h"

class Weapon
{
public:
	Weapon(int ad, float at);

	void Attack(sf::Vector2f startingPos, sf::Vector2f facingDir);
	void Update(float deltaTime);
	void SetWeapon(Item* item);
	WeaponItem* GetWeapon() { return activeWeapon; };
	void Draw(sf::RenderWindow& window);

	void SetAttackBoxPos(sf::Vector2f newPos) { attackbox.setPosition(newPos); }
	Collider GetAttackBox();
	WeaponItem* GetActiveWeapon() { return activeWeapon; }

	void CheckCollision(Entity* enemy);

	bool CanAttack() { return (attackTimer <= 0); }
	void SetShield(bool b) { activeWeapon->SetShield(b); }
	bool ShieldActive() { return activeWeapon->GetShield(); }
	std::vector<Entity*>* GetInRange() { return &inRange; }


private:
	std::vector<Entity*> inRange;
	sf::RectangleShape attackbox;

	int attackDamage;
	float attackTimer;
	float attackTimerMax;

	WeaponItem* activeWeapon;

	int timesAttacked;
};