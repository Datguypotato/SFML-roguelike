#pragma once
#include <SFML/Graphics.hpp>
#include "AnimatorController.h"
#include "Collider.h"
#include "Entity.h"

class Player: public Entity
{
public:
	Player(std::map<std::string, Animation*> animations, float speed, float jumpHeight);
	~Player();

	void Update(float deltaTime) override;
	void OnCollision(sf::Vector2f direction);

private:
	float speed;

	bool canJump;
	float jumpHeight;
};