#include "Player.h"

//Player::Player(std::map<std::string, Animation> animations, int imageCount, float switchTime, float speed, float jumpHeight)
//	:	AC(animations)
//{
//	this->speed = speed;
//	this->jumpHeight = jumpHeight;
//	faceRight = true;
//	canJump = true;
//
//	body.setSize(sf::Vector2f(50, 80));
//	body.setOrigin(body.getSize() / 2.0f);
//}

Player::Player()
	:	anim(),
		canJump(false),
		faceRight(true),
		jumpHeight(),
		speed()
{

}

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight)
	:	anim(texture, imageCount, switchTime)
{
	this->speed = speed;
	this->jumpHeight = jumpHeight;
	faceRight = true;
	canJump = true;

	body.setSize(sf::Vector2f(100, 160));
	body.setOrigin(body.getSize() / 2.0f);
	body.setTexture(texture);
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	velocity.x *= 0.1f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		velocity.x -= speed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		velocity.x += speed;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canJump)
	{
		canJump = false;

		// the video explaining jumping
		// https://youtu.be/v1V3T5BPd7E
		velocity.y = -sqrtf(2.0f * 981.0f * jumpHeight);
	}

	velocity.y += 981.0f * deltaTime;

	if (velocity.x == 0.0f)
	{
		//AC.Play("Default");
	}
	else
	{
		//AC.Play("Walk");

		if (velocity.x > 0.0f)
			faceRight = true;
		else
			faceRight = false;
	}

	//AC.UpdateAnimation(deltaTime, faceRight);
	//AC.GetActiveAnimation().Update(deltaTime, faceRight);
	anim.Update(0, deltaTime, faceRight);
	body.setTextureRect(anim.uvRect);
	//body.setTextureRect(AC.GetActiveAnimation().uvRect);
	body.move(velocity * deltaTime);
}

void Player::OnCollision(sf::Vector2f direction)
{
	if (direction.x < 0.0f)
	{
		// collision on the left
		velocity.x = 0.0f;
	}
	else if (direction.x > 0.0f)
	{
		// collision on the right
		velocity.x = 0.0f;
	}

	if (direction.y < 0.0f)
	{
		// collision down
		velocity.y = 0.0f;
		canJump = true;
	}
	else if(direction.y < 0.0f)
	{
		// collision up
		velocity.y = 0.0f;
	}

}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
