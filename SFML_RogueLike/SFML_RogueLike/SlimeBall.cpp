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
	size = sf::Vector2f(50, 50);
	direction = dir;
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

	body.setSize(size);
	TextureBody.setSize(size);

	AC.Play("Default", faceRight);
	AC.UpdateAnimation(deltaTime, faceRight);
	body.move(velocity * deltaTime);
	TextureBody.setPosition(body.getPosition());
}


void SlimeBall::OnDeath()
{
}

void SlimeBall::SetSize(sf::Vector2f v)
{
	size = v;
	body.setSize(size);
	TextureBody.setSize(size);
}
