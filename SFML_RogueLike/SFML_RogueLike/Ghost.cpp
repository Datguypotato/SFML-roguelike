#include "Ghost.h"

Ghost::Ghost(std::vector<Animation*> animations, sf::Vector2f spawnPosition, sf::RectangleShape* pb)
	:	Enemy(sf::Vector2f(60, 60), sf::Vector2f(30, 30), 50, animations, pb, 150.0f),
		ActionTime(1.5f),
		actionTimeMax(ActionTime),
		blinkDistance(100.0f),
		attackRange(200),
		dashTime(2),
		dashTimeMax(dashTime),
		isDashing(false)
{
	body.setPosition(spawnPosition);
	attackCooldown = 1.6f;
	attackCooldownMax = attackCooldown;
}

Ghost::~Ghost()
{
}

void Ghost::Update(float deltaTime)
{
	Entity::Update(deltaTime);
	std::string playName;
	//std::cout << "Action Time " << ActionTime << std::endl;

	if (!isDashing)
	{
		ActionTime -= deltaTime;
		if (ActionTime <= 0)
		{
			ActionTime = actionTimeMax;
			TextureBody.setFillColor(sf::Color(255, 255, 255, 155));

			if (GetVectorDistance(playerBody->getPosition()) <= attackRange)
			{
				// charge attack
				isDashing = true;
				dashDir = GetPlayerDir();
				playName = "Charge";
				std::cout << "player in range\n";
			}
			else
			{
				// blink towards player
				ActionTime -= deltaTime;
				playName = "Default";

				sf::Vector2f teleportPos = (GetPlayerDir() * blinkDistance) + body.getPosition();

				if (GetPlayerDir().x < 0)
					faceRight = false;
				else if (GetPlayerDir().x >= 0)
					faceRight = true;

				body.setPosition(teleportPos);
			}
		}

	}
	else
	{		
		// attack
		attackCooldown -= deltaTime;
		TextureBody.setFillColor(sf::Color::White);

		if (attackCooldown <= 0)
		{
			playName = "Attack";
			dashTime -= deltaTime;
			if (dashTime <= 0.0f)
			{
				playName = "Default";
				isDashing = false;
				dashTime = dashTimeMax;
				attackCooldown = attackCooldownMax;
			}
			else
			{
				velocity = dashDir * speed;
			}
		}
	}

	body.move(velocity * deltaTime);
	AC.Play(playName, faceRight);
	AC.UpdateAnimation(deltaTime, faceRight);
	TextureBody.setPosition(body.getPosition());
}
