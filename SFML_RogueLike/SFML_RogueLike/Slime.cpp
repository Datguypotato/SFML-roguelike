#include "Slime.h"

Slime::Slime(std::map<std::string, Animation*> animations, sf::Vector2f spawnPosition, sf::RectangleShape* playerbody)
	:	Enemy(sf::Vector2f(59, 59), sf::Vector2f(60, 51), 10, animations, playerbody, 100)
{
	body.setPosition(spawnPosition);

	jumpCoolDownMax = 0.5f;
	jumpCooldown = jumpCoolDownMax;
	jumpHeight = 100.0f;
	jumpRange = 200.0f;
	isJumping = false;
	jumpDir = sf::Vector2f();
	textureOffset = sf::Vector2f();
}

Slime::~Slime()
{
}

void Slime::Update(float deltaTime)
{
	Entity::Update(deltaTime);
	std::string playName;

	jumpCooldown -= deltaTime;
		

	if (jumpCooldown <= 0.0f)
	{
		isJumping = !isJumping;
		jumpCooldown = jumpCoolDownMax;

		if (isJumping)
			jumpDir = GetPlayerDir();

		AC.PlayNoInterupt("Jump", faceRight);
	}

	if (isJumping)
	{
		velocity = jumpDir * speed;
		playName = "Air";
	}
	else
	{
		playName = "Default";
	}

	AC.Play(playName, faceRight);
	AC.UpdateAnimation(deltaTime, faceRight);
	body.move(velocity * deltaTime);
	TextureBody.setPosition(body.getPosition() + textureOffset);
}

void Slime::OnCollision(sf::Vector2f direction)
{
	if (direction.x < 0.0f)
	{
		// collision on the left
		velocity.x *= 0.2f;
	}
	else if (direction.x > 0.0f)
	{
		// collision on the right
		velocity.x *= 0.2f;
	}

	if (direction.y < 0.0f)
	{
		// collision down
		velocity.y *= 0.2f;
	}
	else if (direction.y < 0.0f)
	{
		// collision up
		velocity.y *= 0.2f;
	}
}
