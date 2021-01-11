#include "SlimeBoss.h"

SlimeBoss::SlimeBoss(std::vector<Animation*> animations, sf::Vector2f spawnPosition, Player* player)
	:	SlimeBase(sf::Vector2f(180, 150), sf::Vector2f(120, 100), animations, player, 100, 10, 60, "SlimeBoss"),
		patternTime(2.5f)
{
	body.setPosition(spawnPosition);

	jumpCooldown = 0.5f;
	jumpSpeed = 60.0f;
	bigJumpCoolDown = 1.5f;
	bigJumpSpeed = 160.0f;
	isAlive = true;
	isJumping = false;
	jumpDir = sf::Vector2f();
	activePattern = AttackPattern::Move;
	projectiles = std::vector<SlimeBall*>();
	attackBox = sf::RectangleShape(sf::Vector2f(100, 100));

	events.push_back(new TimeEvent(std::bind(&SlimeBoss::SwitchPattern, this), patternTime, false, "Pattern"));
	events.push_back(new TimeEvent(std::bind(&SlimeBase::JumpToPlayer, this), jumpCooldown, true, "Jump"));
	events.push_back(new TimeEvent(std::bind(&SlimeBoss::Bite, this), 1.0f, true, "Bite"));
	events.push_back(new TimeEvent(std::bind(&SlimeBoss::Shoot, this), 0.5f, false, "Shoot"));

	GetEvent("Jump")->Pause();
	GetEvent("Bite")->Pause();
	GetEvent("Shoot")->Pause();
}

void SlimeBoss::Update(float deltaTime)
{
	Entity::Update(deltaTime);
	SlimeBase::Update(deltaTime);

	switch (activePattern)
	{
	case AttackPattern::Move:
		GetEvent("Pattern")->Play();
		GetEvent("Shoot")->Pause();
		break;
	case AttackPattern::Bite:
		GetEvent("Bite")->Play();
		GetEvent("Jump")->Pause();
		GetEvent("Shoot")->Pause();
		isJumping = true;
		break;
	case AttackPattern::Jump:
		GetEvent("Jump")->Play();
		GetEvent("Shoot")->Pause();
		break;
	case AttackPattern::Projectile:
		GetEvent("Shoot")->Play();
		GetEvent("Jump")->Pause();
		isJumping = false;
		break;
	default:
		break;
	}

	AC.Play(playName, faceRight);
	AC.UpdateAnimation(deltaTime, faceRight);
	body.move(velocity * deltaTime);
	TextureBody.setPosition(body.getPosition());
}

void SlimeBoss::SwitchPattern()
{
	activePattern = AttackPattern::Bite; //static_cast<AttackPattern>(rand() % 4);

	if (activePattern == AttackPattern::Move)
	{
		GetEvent("Jump")->SetInterval(jumpCooldown);
		speed = jumpSpeed;
	}
	else if (activePattern == AttackPattern::Jump)
	{
		GetEvent("Jump")->SetInterval(bigJumpCoolDown);
		speed = bigJumpSpeed;
	}

	//std::cout << (int)activePattern << std::endl;
}

void SlimeBoss::Bite()
{
	UpdateAttackBox();
	AttackPlayer();
}

void SlimeBoss::Shoot()
{
	projectiles.push_back(BuildSlimeBall());
}

SlimeBall* SlimeBoss::BuildSlimeBall()
{
	std::vector<Animation*>* slimeballAnimations = new std::vector<Animation*>();
	sf::Texture* ballTexture = new sf::Texture();

	ballTexture->loadFromFile("Art/SlimeBall.png");
	slimeballAnimations->push_back(new Animation(ballTexture, 1, 1, "Default"));

	SlimeBall* b = new SlimeBall(*slimeballAnimations, GetPlayerDir());
	b->SetPosition(body.getPosition());

	return b;
}

void SlimeBoss::OnHit(const int damage)
{
	std::cout << "SlimeBoss: ";
	Entity::OnHit(damage);
}

void SlimeBoss::Draw(sf::RenderWindow& window)
{
	window.draw(attackBox);
	Entity::Draw(window);
		

	for (SlimeBall* ball : projectiles)
		ball->Draw(window);
}
