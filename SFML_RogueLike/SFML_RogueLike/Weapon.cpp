#include "Weapon.h"

Weapon::Weapon(int ad, float at)
	:	attackDamage(ad),
		attackTimer(at)
{
	attackbox.setSize(sf::Vector2f(50, 50));
	attackbox.setOrigin(attackbox.getSize() / 2.0f);
	attackbox.setTexture(nullptr);
}

void Weapon::Attack()
{
	attackTimer = attackTimerMax;

	for (auto target : inRange)
	{
		target->OnHit(attackDamage);
		inRange.clear();
	}
}

void Weapon::Update(float deltaTime)
{
	attackTimer -= deltaTime;
}

void Weapon::Draw(sf::RenderWindow& window)
{
	if (CanAttack())
		window.draw(attackbox);
}

Collider Weapon::GetAttackBox()
{
	return Collider(attackbox);
}