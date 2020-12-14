#pragma once
#include <functional>

#include "Entity.h"
#include "TimeEvent.h"

class Enemy : public Entity
{
public:
	//TODO: Change it to getting a reff to player instead
	Enemy(sf::Vector2f textureSize, sf::Vector2f bodySize, int health, std::vector<Animation*> animations, sf::RectangleShape* playerBody, float speed, int attackDamage);
	Enemy(sf::Vector2f textureSize, sf::Vector2f bodySize, int health, std::vector<Animation*> animations, sf::RectangleShape* playerBody, float speed, std::function<void(int)> DamagePlayer, int attackDamage);
	Enemy(const Enemy& rhs);
	~Enemy();

	virtual Entity* Clone() const override;
	void LookAtPlayer();

	sf::Vector2f GetPlayerDir();
	float GetVectorDistance(sf::Vector2f target);
	void UpdateAttackBox();

	std::vector<TimeEvent*> GetEvents() { return events; }

protected:
	sf::RectangleShape* playerBody;
	sf::RectangleShape attackBox;

	std::vector<TimeEvent*> events;

	std::function<void(int)> DamagePlayer;
};

