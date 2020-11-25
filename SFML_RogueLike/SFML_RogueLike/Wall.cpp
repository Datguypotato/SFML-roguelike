#include "Wall.h"

Wall::Wall(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position)
	:	Ground(texture, size, position)
{
}

Wall::~Wall()
{
}
