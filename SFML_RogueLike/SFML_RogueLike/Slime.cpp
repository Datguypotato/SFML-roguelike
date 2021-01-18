#include "Slime.h"

Slime::Slime(std::vector<Animation*> animations, sf::Vector2f spawnPosition, Player* player)
	:	SlimeBase(sf::Vector2f(59, 59), sf::Vector2f(60, 51), animations, player, 2, 1, 50, "Slime")
{
	body.setPosition(spawnPosition);

	isAlive = true;
	jumpCoolDownMax = 0.5f;
	jumpCooldown = jumpCoolDownMax;
	isJumping = false;
	jumpDir = sf::Vector2f();

	events.push_back(new TimeEvent(std::bind(&SlimeBase::JumpToPlayer, this), jumpCooldown, false, "Jump"));

	jumpSound.loadFromFile("Audio/sfx_sound_neutral6.wav");
	sound.setBuffer(jumpSound);
}

// for the Slime boss
Slime::Slime(sf::Vector2f textureSize, sf::Vector2f bodySize, int health, std::vector<Animation*> animations, Player* player, float speed, sf::Vector2f spawnPosition)
	:	SlimeBase(textureSize, bodySize, animations, player, health, speed, 20, "SlimeBoss")
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
	:	SlimeBase(rhs)
{
	jumpCoolDownMax = rhs.jumpCoolDownMax;
	jumpCooldown = jumpCoolDownMax;
	isJumping = rhs.isJumping;
	jumpDir = rhs.jumpDir;
}

void Slime::Update(float deltaTime)
{
	Entity::Update(deltaTime);
	SlimeBase::Update(deltaTime);

	if (effecthandler->IsStunned())
		GetEvent("Jump")->Pause();
	else
		GetEvent("Jump")->Play();

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
	}
	else if (direction.y < 0.0f)
	{
		// collision up
		velocity.y *= 0.2f;
	}
}
