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
	Entity(sf::Vector2f textureSize, sf::Vector2f bodySize, int health, std::vector<Animation*> animations, float speed, int attackDamage, std::string n);
	Entity(sf::Vector2f bodySize, int health, std::vector<Animation*> animations, float speed, int attackDamage, std::string n);
	virtual ~Entity();
	Entity(const Entity& rhs);

	virtual void Update(float deltaTime);
	virtual void Draw(sf::RenderWindow& window);

	virtual void OnCollision(sf::Vector2f direction);
	virtual void OnHit(const int damage, Entity* damageDealer);
	virtual void OnHit(const int damage);
	virtual void OnDeath();

	Collider GetCollider() { return Collider(body); }
	sf::RectangleShape* GetBody() { return &body; };
	sf::RectangleShape* GetTextureBody() { return &TextureBody; };

	sf::Vector2f GetPosition() { return body.getPosition(); }
	void SetPosition(sf::Vector2f pos) { body.setPosition(pos); }

	sf::Vector2f GetBodySize() { return body.getSize(); }
	void SetBodySize(sf::Vector2f size) { return body.setSize(size); }

	sf::Sound GetSound() { return sound; }
	EffectHandler* GetEffectHandler() { return effecthandler; }
	AnimatorController GetAC() { return AC; }
	int GetAttackDamage() { return attackDamage; }
	void AddAttackDamage(int a) { attackDamage += a; }
	int GetHealth() { return health; }
	int GetMaxHealth() { return maxHealth; }
	void AddMaxHealth(int value) { maxHealth += value; }
	void Heal(int healValue);

	bool GetAliveStatus() { return isAlive; }
	void SetAliveStatus(bool b) { isAlive = b; }

	sf::Vector2i GetGridPosition() { return static_cast<sf::Vector2i>(body.getPosition()); }

protected:
	void GetEffects();
	TimeEvent* GetEvent(std::string n);

	sf::RectangleShape TextureBody;
	sf::RectangleShape body;
	std::string name;

	std::string playName;
	AnimatorController AC;
	bool faceRight;
	std::vector<TimeEvent*> events;

	int attackDamage;
	float speed;
	bool isAlive;
	int health;
	int maxHealth;

	EffectHandler* effecthandler;
	float damageCooldown;
	float damageCooldownMax;

	sf::Vector2f velocity;

	sf::Sound sound;
	sf::SoundBuffer hitSound;
};