#pragma once
#include<SFML/Graphics.hpp>

class Collider
{
public:
	Collider(sf::RectangleShape& body);
	~Collider();


	void Move(float dx, float dy) { body.move(dx, dy); }

	bool CheckCollision(Collider& other, float push);
	bool CheckTrigger(Collider& other);
	bool CheckTrigger(sf::Vector2f other);
	sf::RectangleShape& GetBody() { return body; }
	sf::Vector2f GetPosition() { return body.getPosition(); }
	sf::Vector2f GetHalfSize() { return body.getSize() / 2.0f; }

protected:
	sf::RectangleShape& body;
};

