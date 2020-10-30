#include "Player.h"

Player::Player(std::map<std::string, Animation*> animations, int imageCount, float switchTime, float speed, float jumpHeight)
	:	Entity(sf::Vector2f(50, 80), sf::Vector2f(50, 70)),
		AC(animations)
{
	this->speed = speed;
	this->jumpHeight = jumpHeight;
	faceRight = true;
	canJump = true;

	TextureBody.setTexture(AC.GetActiveAnimation()->GetTexture());
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	Entity::Update(deltaTime);
	std::string playName;
	velocity.x *= 0.1f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		velocity.x -= speed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		velocity.x += speed;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		AC.PlayNoInterupt("Attack", faceRight);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canJump)
	{
		canJump = false;

		// the video explaining jumping
		// https://youtu.be/v1V3T5BPd7E
		velocity.y = -sqrtf(2.0f * 981.0f * jumpHeight);
	}

	if (velocity.x != 0.0f)
	{
		playName = "Walk";
	}
	else
	{
		playName = "Default";
	}

	if (abs(velocity.y) > 10.0f)
		playName = "Jump";

	if (TextureBody.getTexture() != AC.GetActiveAnimation()->GetTexture())
		TextureBody.setTexture(AC.GetActiveAnimation()->GetTexture());

	if(TextureBody.getTextureRect() != AC.GetActiveAnimation()->uvRect)
		TextureBody.setTextureRect(AC.GetActiveAnimation()->uvRect);
	
	AC.Play(playName, faceRight);
	AC.UpdateAnimation(deltaTime, faceRight);
	body.move(velocity * deltaTime);
	TextureBody.setPosition(body.getPosition());
}

void Player::OnCollision(sf::Vector2f direction)
{
	Entity::OnCollision(direction);
	if (direction.y < 0.0f)
	{
		// collision down
		canJump = true;
	}
}
