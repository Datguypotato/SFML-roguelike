#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Collider.h"
#include "AnimatorController.h"

class Entity
{
public:
	Entity(sf::Vector2f textureSize, sf::Vector2f bodySize, int health, std::vector<Animation*> animations, float speed, int attackDamage);
	virtual ~Entity();
	Entity(const Entity& rhs);
	virtual Entity* Clone() const = 0;

	virtual void Update(float deltaTime);
	virtual void Draw(sf::RenderWindow& window);

	virtual void OnCollision(sf::Vector2f direction);
	Collider GetCollider() { return Collider(body); }
	sf::RectangleShape* GetBody() { return &body; };

	virtual void OnHit(const int damage);

	sf::Vector2f GetPosition() { return body.getPosition(); }
	void SetPosition(sf::Vector2f pos) { body.setPosition(pos); }

	AnimatorController GetAC() { return AC; }
	int GetAttackDamage() { return attackDamage; }

protected:
	sf::RectangleShape TextureBody;
	sf::RectangleShape body;

	std::string playName;
	AnimatorController AC;
	bool faceRight;

	int attackDamage;
	float speed;
	bool isAlive;
	int health;

	float damageCooldown;
	float damageCooldownMax;

	sf::Vector2f velocity;

	sf::Sound sound;
};