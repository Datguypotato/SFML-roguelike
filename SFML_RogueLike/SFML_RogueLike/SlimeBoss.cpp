#include "SlimeBoss.h"

SlimeBoss::SlimeBoss(std::vector<Animation*> animations, sf::Vector2f spawnPosition, Player* player)
	:	SlimeBase(sf::Vector2f(180, 180), sf::Vector2f(200, 200), animations, player, 100, 10, 60),
		patternTime(1.5f)
{
	body.setPosition(spawnPosition);

	isAlive = true;
	jumpCooldown = 0.5f;
	isJumping = false;
	jumpDir = sf::Vector2f();
	activePattern = AttackPattern::Move;

	events.push_back(new TimeEvent(std::bind(&SlimeBoss::SwitchPattern, this), patternTime));
	events.push_back(new TimeEvent(std::bind(&SlimeBase::JumpToPlayer, this), jumpCooldown));

	events[1]->Pause();
}

void SlimeBoss::Update(float deltaTime)
{
	Entity::Update(deltaTime);
	SlimeBase::Update(deltaTime);

	switch (activePattern)
	{
	case AttackPattern::Move:
		events[1]->Play();
		break;
	case AttackPattern::Bite:
		// bite player
		break;
	case AttackPattern::Jump:
		// jump
		break;
	case AttackPattern::Projectile:
		// shoot
		break;
	default:
		break;
	}
	//playName = "Default";

	AC.Play(playName, faceRight);
	AC.UpdateAnimation(deltaTime, faceRight);
	body.move(velocity * deltaTime);
	TextureBody.setPosition(body.getPosition());
}

void SlimeBoss::SwitchPattern()
{
	activePattern = AttackPattern::Move; //static_cast<AttackPattern>(rand() % 4);
	std::cout << (int)activePattern << std::endl;
}

void SlimeBoss::OnHit(const int damage)
{
	std::cout << "SlimeBoss: ";
	Entity::OnHit(damage);
}