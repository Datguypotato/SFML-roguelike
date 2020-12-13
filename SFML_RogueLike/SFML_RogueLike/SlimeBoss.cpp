//#include "SlimeBoss.h"
//
//SlimeBoss::SlimeBoss(std::vector<Animation*> animations, sf::Vector2f spawnPosition, sf::RectangleShape* playerBody)
//	:	Slime(sf::Vector2f(250, 250), sf::Vector2f(200,200), 200, animations, playerBody, 50, spawnPosition),
//		patternTime(1.5f),
//		patternTimeMax(patternTime)
//{
//	isAlive = true;
//	jumpCoolDownMax = 0.5f;
//	jumpCooldown = jumpCoolDownMax;
//	isJumping = false;
//	jumpDir = sf::Vector2f();
//	activePattern = AttackPattern::Move;
//}
//
//void SlimeBoss::Update(float deltaTime)
//{
//	Entity::Update(deltaTime);
//
//	patternTime -= deltaTime;
//	if (patternTime <= 0)
//	{
//		patternTime = patternTimeMax;
//		activePattern = AttackPattern::Move; //static_cast<AttackPattern>(rand() % 4);
//		std::cout << (int)activePattern << std::endl;
//	}
//
//	switch (activePattern)
//	{
//	case AttackPattern::Move:
//		Slime::JumpToPlayer(deltaTime);
//		break;
//	case AttackPattern::Bite:
//		// bite player
//		break;
//	case AttackPattern::Jump:
//		// jump
//		break;
//	case AttackPattern::Projectile:
//		// shoot
//		break;
//	default:
//		break;
//	}
//	//playName = "Default";
//
//	AC.Play(playName, faceRight);
//	AC.UpdateAnimation(deltaTime, faceRight);
//	body.move(velocity * deltaTime);
//	TextureBody.setPosition(body.getPosition());
//}