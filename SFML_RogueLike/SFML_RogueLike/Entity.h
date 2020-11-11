#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Collider.h"
#include "AnimatorController.h"

class Entity
{
public:
	Entity(sf::Vector2f textureSize, sf::Vector2f bodySize, int health, std::map<std::string, Animation*> animations, float speed);
	~Entity();
	Entity(const Entity& rhs);

	virtual void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);

	virtual void OnCollision(sf::Vector2f direction);
	void OnHit(int damage);

	sf::Vector2f GetPosition() { return body.getPosition(); }
	Collider GetCollider() { return Collider(body); }

protected:
	sf::RectangleShape TextureBody;
	sf::RectangleShape body;

	AnimatorController AC;
	bool faceRight;

	float speed;
	bool isAlive;
	int health;

	sf::Vector2f velocity;

	sf::Sound sound;
};