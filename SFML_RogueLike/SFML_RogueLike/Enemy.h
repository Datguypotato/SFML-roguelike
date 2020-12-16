#pragma once
#include <functional>

#include "TimeEvent.h"
#include "Entity.h"
#include "Player.h"

class Enemy : public Entity
{
public:
	//TODO: Change it to getting a reff to player instead
	Enemy(sf::Vector2f textureSize, sf::Vector2f bodySize, int health, std::vector<Animation*> animations, Player* player, float speed, int attackDamage);
	Enemy(const Enemy& rhs);
	~Enemy();

	virtual Entity* Clone() const override;
	void LookAtPlayer();

	sf::Vector2f GetPlayerDir();
	float GetVectorDistance(sf::Vector2f target);
	void UpdateAttackBox();

	std::vector<TimeEvent*> GetEvents() { return events; }

protected:
	Player* player;
	sf::RectangleShape* playerBody;
	sf::RectangleShape attackBox;

	std::function<void(int)> DamagePlayer;

	std::vector<TimeEvent*> events;
};

