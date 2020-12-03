#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Collider.h"
#include "AnimatorController.h"

class Entity
{
public:
	Entity(sf::Vector2f textureSize, sf::Vector2f bodySize, int health, std::vector<Animation*> animations, float speed);
	virtual ~Entity();
	Entity(const Entity& rhs);
	virtual Entity* Clone() const = 0;

	virtual void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);

	virtual void OnCollision(sf::Vector2f direction);
	Collider GetCollider() { return Collider(body); }
	sf::RectangleShape* GetBody() { return &body; };

	void OnHit(const int damage);

	sf::Vector2f GetPosition() { return body.getPosition(); }
	void SetPosition(sf::Vector2f pos) { body.setPosition(pos); }

	AnimatorController GetAC() { return AC; }

protected:
	sf::RectangleShape TextureBody;
	sf::RectangleShape body;

	AnimatorController AC;
	bool faceRight;

	float speed;
	bool isAlive;
	int health;
	float damageCooldown;
	float damageCooldownMax;

	sf::Vector2f velocity;

	sf::Sound sound;
};