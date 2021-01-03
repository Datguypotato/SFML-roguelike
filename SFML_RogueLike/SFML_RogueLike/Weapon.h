#pragma once
#include <SFML/Graphics.hpp>

#include "Entity.h"
#include "Collider.h"

class Weapon
{
public:
	Weapon(int ad, float at);

	void Attack();
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);

	void SetAttackBoxPos(sf::Vector2f newPos) { attackbox.setPosition(newPos); }
	Collider GetAttackBox();

	bool CanAttack() { return (attackTimer <= 0); }
	std::vector<Entity*>* GetInRange() { return &inRange; }
private:
	std::vector<Entity*> inRange;
	sf::RectangleShape attackbox;

	int attackDamage;
	float attackTimer;
	float attackTimerMax;
};