#include "Enemy.h"

Enemy::Enemy(sf::Vector2f textureSize, sf::Vector2f bodySize, int health, std::map<std::string, Animation*> animations, sf::RectangleShape* playerBody)
	:	Entity(sf::Vector2f(59, 51), sf::Vector2f(60, 51), 10, animations)
{
	this->playerBody = playerBody;
}

Enemy::~Enemy()
{
}

void Enemy::LookAtPlayer()
{
}

sf::Vector2f Enemy::GetPlayerDir()
{	
	sf::Vector2f delta = (playerBody->getPosition() - body.getPosition());
	float temp = (float)sqrt(delta.x * delta.x + delta.y * delta.y);
	return delta / temp;
}
