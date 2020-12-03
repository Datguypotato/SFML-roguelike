#include "Goblin.h"

Goblin::Goblin(std::vector<Animation*> animations, sf::Vector2f spawnPosition, sf::RectangleShape* playerbody)
	:	Enemy(sf::Vector2f(66,57), sf::Vector2f(60, 55), 20, animations, playerBody, 120)
{
}

Goblin::~Goblin()
{
}

void Goblin::Update(float deltaTime)
{
}
