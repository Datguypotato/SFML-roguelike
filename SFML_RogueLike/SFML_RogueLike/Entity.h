#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Collider.h"
#include "AnimatorController.h"
#include "EffectHandler.h"
#include "TimeEvent.h"

class Entity
{
public:
	Entity(sf::Vector2f textureSize, sf::Vector2f bodySize, int health, std::vector<Animation*> animations, float speed, int attackDamage);
	Entity(sf::Vector2f bodySize, int health, std::vector<Animation*> animations, float speed, int attackDamage);
	virtual ~Entity();
	Entity(const Entity& rhs);

	virtual void Update(float deltaTime);
	virtual void Draw(sf::RenderWindow& window);

	virtual void OnCollision(sf::Vector2f direction);
	virtual void OnHit(const int damage);
	virtual void OnDeath();

	Collider GetCollider() { return Collider(body); }
	sf::RectangleShape* GetBody() { return &body; };

	sf::Vector2f GetPosition() { return body.getPosition(); }
	void SetPosition(sf::Vector2f pos) { body.setPosition(pos); }

	sf::Sound GetSound() { return sound; }
	std::vector<TimeEvent*> GetEvents() { return events; }
	EffectHandler* GetEffectHandler() { return effecthandler; }
	AnimatorController GetAC() { return AC; }
	int GetAttackDamage() { return attackDamage; }
	int GetHealth() { return health; }

	bool GetAliveStatus() { return isAlive; }

protected:
	void GetEffects();

	sf::RectangleShape TextureBody;
	sf::RectangleShape body;

	std::string playName;
	AnimatorController AC;
	bool faceRight;
	std::vector<TimeEvent*> events;

	int attackDamage;
	float speed;
	bool isAlive;
	int health;

	EffectHandler* effecthandler;
	float damageCooldown;
	float damageCooldownMax;

	sf::Vector2f velocity;

	sf::Sound sound;
};