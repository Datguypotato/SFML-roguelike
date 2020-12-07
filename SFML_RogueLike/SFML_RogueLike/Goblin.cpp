#include "Goblin.h"

Goblin::Goblin(std::vector<Animation*> animations, sf::Vector2f spawnPosition, sf::RectangleShape* pb)
	:	Enemy(sf::Vector2f(66,57), sf::Vector2f(60, 55), 20, animations, pb, 120),
		attackRange(100.0f),
		isAttacking(false),
		windupAttackTime(3.0f)
{
	body.setPosition(spawnPosition);
}

Goblin::~Goblin()
{
}

void Goblin::Update(float deltaTime)
{
	Entity::Update(deltaTime);
	std::string playName = "Default";

	if (!isAttacking)
	{
		if (GetVectorDistance(playerBody->getPosition()) < attackRange)
		{
			//std::cout << "Player in range\n";
			// player in range
			isAttacking = true;

		}
		else
		{
			// move towards player
			velocity = GetPlayerDir() * speed;
		}
	}
	else
	{
		// attack
		windupAttackTime -= deltaTime;
		if (windupAttackTime <= 0.0f)
			isAttacking = false;
	}

	AC.Play(playName, faceRight);
	AC.UpdateAnimation(deltaTime, faceRight);
	body.move(velocity * deltaTime);
	TextureBody.setPosition(body.getPosition());
}
