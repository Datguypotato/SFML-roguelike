#include "Ghost.h"

Ghost::Ghost(std::vector<Animation*> animations, sf::Vector2f spawnPosition, Player* player)
	:	Enemy(sf::Vector2f(60, 60), sf::Vector2f(30, 30), 50, animations, player, 150.0f, 10),
		blinkDistance(100.0f),
		attackRange(200),
		dashTime(2.0f),
		actionTime(1.5f),
		attackCooldown(1.5f),
		isDashing(false)
{
	events.push_back(new TimeEvent(std::bind(&Ghost::Action, this), actionTime, false, "Action"));
	events.push_back(new TimeEvent(std::bind(&Ghost::StopDash, this), dashTime, true, "StopDash"));

	body.setPosition(spawnPosition);
}

Ghost::~Ghost()
{
}

void Ghost::Update(float deltaTime)
{
	Entity::Update(deltaTime);
	std::string playName;

	if (isDashing)
	{
		playName = "Attack";
		velocity = dashDir * speed;
	}
	else
	{
		playName = "Default";
	}

	body.move(velocity * deltaTime);
	AC.Play(playName, faceRight);
	AC.UpdateAnimation(deltaTime, faceRight);
	TextureBody.setPosition(body.getPosition());
}

void Ghost::Action()
{
	if (!isDashing)
	{
		// if in attack range
		if (GetVectorDistance(playerBody->getPosition()) <= attackRange)
		{
			playName = "Charge";
			TextureBody.setFillColor(sf::Color::White);
			isDashing = true;
			dashDir = GetPlayerDir();
			GetEvent("StopDash")->Play();
		}
		else
		{
			playName = "Default";
			TextureBody.setFillColor(sf::Color(255, 255, 255, 155));
			BlinkToPlayer();
		}
	}
}

void Ghost::BlinkToPlayer()
{
	sf::Vector2f teleportPos = (GetPlayerDir() * blinkDistance + body.getPosition());
	body.setPosition(teleportPos);
}

void Ghost::StopDash()
{
	isDashing = false;
}

void Ghost::OnHit(const int damage)
{
	std::cout << "Ghost: ";
	Entity::OnHit(damage);
}