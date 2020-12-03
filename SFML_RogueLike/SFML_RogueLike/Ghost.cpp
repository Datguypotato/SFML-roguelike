#include "Ghost.h"

Ghost::Ghost(std::vector<Animation*> animations, sf::Vector2f spawnPosition, sf::RectangleShape* pb)
	:	Enemy(sf::Vector2f(48, 54), sf::Vector2f(45, 50), 50, animations, pb, 150.0f),
		blinkTime(3.0f),
		blinkTimeMax(blinkTime),
		blinkDistance(100.0f),
		attackRange(250),
		dashTime(2),
		dashTimeMax(dashTime),
		isDashing(false)
{
	body.setPosition(spawnPosition);
	attackCooldown = 2.0f;
	attackCooldownMax = attackCooldown;
}

Ghost::~Ghost()
{
}

void Ghost::Update(float deltaTime)
{
	Entity::Update(deltaTime);
	std::string playName;

	attackCooldown -= deltaTime;
	//TODO: the timming is rubbish either split the animation in 2 or time it better
	if (!isDashing)
	{
		if (GetVectorDistance(playerBody->getPosition()) < attackRange && attackCooldown <= 0)
		{
			// do dash attack
			isDashing = true;
			dashDir = GetPlayerDir();
			playName = "Attack";
			std::cout << "player in range\n";
		}
		else
		{
			//blink towards player
			blinkTime -= deltaTime;
			playName = "Default";

			if (blinkTime <= 0)
			{
				sf::Vector2f teleportPos = (GetPlayerDir() * blinkDistance) + body.getPosition();
				blinkTime -= deltaTime;
				blinkTime = blinkTimeMax;

				if (GetPlayerDir().x < 0)
					faceRight = false;
				else if(GetPlayerDir().x >= 0)
					faceRight = true;

				body.setPosition(teleportPos);
			}
		}
	}
	else
	{
		//std::cout << "Attack cooldown " << attackCooldown << std::endl;		
		if (attackCooldown <= 0)
		{
			playName = "Attack";
			dashTime -= deltaTime;
			if (dashTime <= 0.0f)
			{
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
