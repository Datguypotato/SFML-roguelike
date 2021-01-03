#include "SlimeBall.h"

SlimeBall::SlimeBall(std::vector<Animation*> animations, sf::Vector2f dir)
	:	Entity(sf::Vector2f(50,50), sf::Vector2f(50,50), 1, animations, 200, 10)
{
	direction = dir;
}

void SlimeBall::Update(float deltaTime)
{
	Entity::Update(deltaTime);
	velocity = direction * speed;


	AC.Play("Default", faceRight);
	AC.UpdateAnimation(deltaTime, faceRight);
	body.move(velocity * deltaTime);
	TextureBody.setPosition(body.getPosition());
}

void SlimeBall::OnHit(const int damage)
{
	if (damageCooldown <= 0)
	{
		damageCooldown = damageCooldownMax;
		if (health - damage <= 0)
		{
			health = 0;
			isAlive = false;
			OnDeath();
		}
		else
		{
			health -= damage;
		}
	}
}

void SlimeBall::OnDeath()
{
}