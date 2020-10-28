#pragma once
#include <SFML/Graphics.hpp>
#include "AnimatorController.h"
#include "Collider.h"

class Player
{
public:
	Player();
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight);
	~Player();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void OnCollision(sf::Vector2f direction);

	sf::Vector2f GetPosition() { return body.getPosition(); }
	Collider GetCollider() { return Collider(body); }

	//Animation GetAnimation() { return animation; }

private:
	sf::RectangleShape body;
	//AnimatorController AC;
	Animation anim;
	float speed;
	bool faceRight;

	sf::Vector2f velocity;
	bool canJump;
	float jumpHeight;
};

