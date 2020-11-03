#include "Slime.h"

Slime::Slime(std::map<std::string, Animation*> animations, sf::Vector2f spawnPosition, sf::RectangleShape* playerbody)
	:	Enemy(sf::Vector2f(59, 51), sf::Vector2f(60, 51), 10, animations, playerbody)
{
	body.setPosition(spawnPosition);

	jumpCoolDownMax = 2;
	jumpCooldown = jumpCoolDownMax;
	jumpHeight = 100.0f;
	jumpRange = 200.0f;
}

Slime::~Slime()
{
}

void Slime::Update(float deltaTime)
{
	Entity::Update(deltaTime);
	std::string playName;



	if (onGround)
	{
		jumpCooldown -= deltaTime;
		velocity.x *= 0.1f;
	}
		

	if (jumpCooldown <= 0.0f)
	{
		jumpCooldown = jumpCoolDownMax;
		onGround = false;
		velocity.y = -sqrtf(2.0f * 981.0f * jumpHeight);
		velocity.x = jumpRange * GetPlayerDir().x;

		LookAtPlayer();
	}

	if (onGround)
		playName = "Default";
	else
		playName = "Jump";


	AC.Play(playName, faceRight);
	AC.UpdateAnimation(deltaTime, faceRight);
	body.move(velocity * deltaTime);
	TextureBody.setPosition(body.getPosition());
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
		onGround = true;
	}
	else if (direction.y < 0.0f)
	{
		// collision up
		velocity.y *= 0.2f;
	}
}
