#include "SlimeBase.h"

SlimeBase::SlimeBase(sf::Vector2f textureSize, sf::Vector2f bodySize, std::vector<Animation*> animations, Player* player, int health, int attackDamage, float speed, std::string n)
	:	Enemy(textureSize, bodySize, health, animations, player, speed, attackDamage, n),
		jumpCooldown(),
		isJumping(false),
		jumpDir()
{
	jumpSound.loadFromFile("Audio/sfx_sound_neutral6.wav");
}

void SlimeBase::Update(float deltaTime)
{
	if (isJumping)
	{
		velocity = jumpDir * speed;
		playName = "Air";
	}
	else
	{
		playName = "Default";
	}
}

void SlimeBase::JumpToPlayer()
{
	isJumping = !isJumping;

	if (isJumping)
	{
		jumpDir = GetPlayerDir();
		sound.setBuffer(jumpSound);
		sound.play();
	}
	AC.PlayNoInterupt("Jump", faceRight);
}
