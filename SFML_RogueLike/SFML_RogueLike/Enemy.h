#pragma once
#include "Entity.h"

class Enemy : public Entity
{
public:
	Enemy(sf::Vector2f textureSize, sf::Vector2f bodySize, int health, std::map<std::string, Animation*> animations, sf::RectangleShape* playerBody, float speed);
	Enemy(const Enemy& rhs);
	~Enemy();

	virtual Entity* Clone() const override;
	void LookAtPlayer();

	sf::Vector2f GetPlayerDir();

protected:
	sf::RectangleShape* playerBody;
};
