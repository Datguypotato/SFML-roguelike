#pragma once
#include "Ground.h"
class Wall :   public Ground
{
public:
	Wall(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);
	~Wall();
};

