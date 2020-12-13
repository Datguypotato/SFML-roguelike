#include "Slime.h"

Slime::Slime(std::vector<Animation*> animations, sf::Vector2f spawnPosition, sf::RectangleShape* playerbody)
	:	Enemy(sf::Vector2f(59, 59), sf::Vector2f(60, 51), 10, animations, playerbody, 100)
{
	body.setPosition(spawnPosition);

	isAlive = true;
	jumpCoolDownMax = 0.5f;
	jumpCooldown = jumpCoolDownMax;
	isJumping = false;
	jumpDir = sf::Vector2f();

	jumpSound.loadFromFile("Audio/sfx_sound_neutral6.wav");
	sound.setBuffer(jumpSound);
}

// for the Slime boss
Slime::Slime(sf::Vector2f textureSize, sf::Vector2f bodySize, int health, std::vector<Animation*> animations, sf::RectangleShape* playerBody, float speed, sf::Vector2f spawnPosition)
	:	Enemy(textureSize, bodySize, health, animations, playerBody, speed)
{
	body.setPosition(spawnPosition);

	isAlive = true;
	jumpCoolDownMax = 0.5f;
	jumpCooldown = jumpCoolDownMax;
	isJumping = false;
	jumpDir = sf::Vector2f();

	jumpSound.loadFromFile("Audio/sfx_sound_neutral6.wav");
	sound.setBuffer(jumpSound);
}

Slime::~Slime()
{
}

Slime::Slime(const Slime& rhs)
	:	Enemy(rhs)
{
	jumpCoolDownMax = rhs.jumpCoolDownMax;
	jumpCooldown = jumpCoolDownMax;
	isJumping = rhs.isJumping;
	jumpDir = rhs.jumpDir;
}

Slime* Slime::Clone() const
{
	return new Slime(*this);
}

void Slime::Update(float deltaTime)
{
	Entity::Update(deltaTime);

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
	TextureBody.setPosition(body.getPosition());
}

void Slime::JumpToPlayer()
{
	isJumping = !isJumping;
	jumpCooldown = jumpCoolDownMax;

	if (isJumping)
	{
		jumpDir = GetPlayerDir();
		sound.play();
	}
	AC.PlayNoInterupt("Jump", faceRight);

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


