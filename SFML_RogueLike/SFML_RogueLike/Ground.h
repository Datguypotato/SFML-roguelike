#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"

class Ground
{
public:
	Ground(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);
	~Ground();

	void Draw(sf::RenderWindow& window);
	Collider GetCollider() { return Collider(body); }
	
protected:
	sf::RectangleShape body;
};

