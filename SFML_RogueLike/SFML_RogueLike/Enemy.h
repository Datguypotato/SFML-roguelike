#pragma once
#include <functional>

#include "TimeEvent.h"
#include "Entity.h"
#include "Player.h"

class Enemy : public Entity
{
public:
	Enemy(sf::Vector2f textureSize, sf::Vector2f bodySize, int health, std::vector<Animation*> animations, Player* player, float speed, int attackDamage, std::string n);
	Enemy(const Enemy& rhs);
	~Enemy();

	void LookAtPlayer();

	sf::Vector2f GetPlayerDir();
	float GetVectorDistance(sf::Vector2f target);
	void UpdateAttackBox();

protected:
	void AttackPlayer();

	Player* player;
	sf::RectangleShape* playerBody;
	sf::RectangleShape attackBox;
};

