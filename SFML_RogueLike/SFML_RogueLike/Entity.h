#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"

class Entity
{
public:
	Entity(sf::Vector2f textureSize, sf::Vector2f bodySize);
	~Entity();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void OnCollision(sf::Vector2f direction);

	sf::Vector2f GetPosition() { return body.getPosition(); }
	Collider GetCollider() { return Collider(body); }

protected:
	sf::RectangleShape TextureBody;
	sf::RectangleShape body;

	bool faceRight;

	sf::Vector2f velocity;
};

