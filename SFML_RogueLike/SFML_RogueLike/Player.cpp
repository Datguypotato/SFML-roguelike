#include "Player.h"

Player::Player(std::map<std::string, Animation*> animations, float speed)
	: Entity(sf::Vector2f(50, 80), sf::Vector2f(50, 70), 100, animations, speed)
{
	body.setPosition(sf::Vector2f(0, 0));
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	Entity::Update(deltaTime);

	std::string playName;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		velocity.x -= speed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		velocity.x += speed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		velocity.y += speed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		velocity.y -= speed;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		AC.PlayNoInterupt("Attack", faceRight);

	if (velocity.x != 0.0f || velocity.y != 0.0f)
		playName = "Walk";
	else
		playName = "Default";
	
	AC.Play(playName, faceRight);
	AC.UpdateAnimation(deltaTime, faceRight);
	body.move(velocity * deltaTime);
	TextureBody.setPosition(body.getPosition());
}

