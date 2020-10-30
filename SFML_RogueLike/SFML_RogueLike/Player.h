#pragma once
#include <SFML/Graphics.hpp>
#include "AnimatorController.h"
#include "Collider.h"
#include "Entity.h"

class Player: public Entity
{
public:
	//Player(sf::Texture* texture, int imageCount, float switchTime, float speed, float jumpHeight);
	Player(std::map<std::string, Animation*> animations, int imageCount, float switchTime, float speed, float jumpHeight);
	~Player();

	void Update(float deltaTime);
	void OnCollision(sf::Vector2f direction);

	sf::Vector2f GetPosition() { return body.getPosition(); }
	Collider GetCollider() { return Collider(body); }


private:
	AnimatorController AC;
	float speed;

	bool canJump;
	float jumpHeight;
};

