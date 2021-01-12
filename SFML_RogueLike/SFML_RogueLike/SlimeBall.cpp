#include "SlimeBall.h"

/// <summary>
/// For SlimeBoss
/// Default damage = 10
/// </summary>
/// <param name="animations"></param>
/// <param name="dir"></param>
SlimeBall::SlimeBall(std::vector<Animation*> animations, sf::Vector2f dir)
	:	Entity(sf::Vector2f(50,50), sf::Vector2f(50,50), 1, animations, 200, 10, "SlimeBall")
{
	direction = dir;
	HitDamage = 10;
}

/// <summary>
/// Window weapon
/// </summary>
/// <param name="animations"></param>
/// <param name="direction"></param>
/// <param name="dmg"></param>
SlimeBall::SlimeBall(std::vector<Animation*> animations, sf::Vector2f direction, int dmg)
	:	SlimeBall(animations, direction)
{
	attackDamage = dmg;
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