#include "Player.h"

Player::Player(std::vector<Animation*> animations, float speed, int attackDamage)
	:	Entity(sf::Vector2f(50, 80), sf::Vector2f(50, 70), 100, animations, speed, attackDamage),
		attackTimer(1.0f),
		attackTimerMax(attackTimer)
{
	body.setPosition(sf::Vector2f(150, 150));
	attackbox.setSize(sf::Vector2f(50, 50));
	attackbox.setOrigin(attackbox.getSize() / 2.0f);
	attackbox.setTexture(nullptr);
}

Player::~Player()
{
}

Player::Player(const Player& rhs)
	:	Entity(rhs)
{
	
}

Player* Player::Clone() const
{
	return new Player(*this);
}

void Player::Update(float deltaTime)
{
	Entity::Update(deltaTime);

	std::string playName;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		velocity.x -= speed;
		attackbox.setPosition(body.getPosition() - sf::Vector2f(body.getSize().x, 0));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		velocity.x += speed;
		attackbox.setPosition(body.getPosition() - sf::Vector2f(-body.getSize().x, 0));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		velocity.y += speed;
		attackbox.setPosition(body.getPosition() - sf::Vector2f(0, -body.getSize().y));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		velocity.y -= speed;
		attackbox.setPosition(body.getPosition() - sf::Vector2f(0, body.getSize().y));
	}


	attackTimer -= deltaTime;
	if (CanAttack())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		{
			AC.PlayNoInterupt("Attack", faceRight);
			attackTimer = attackTimerMax;

			for (auto target : inRange)
			{
				target->OnHit(attackDamage);
				inRange.erase(inRange.begin());
			}
		}
	}


	if (velocity.x != 0.0f || velocity.y != 0.0f)
		playName = "Walk";
	else
		playName = "Default";
	

	
	AC.Play(playName, faceRight);
	AC.UpdateAnimation(deltaTime, faceRight);
	body.move(velocity * deltaTime);
	TextureBody.setPosition(body.getPosition());
}

Collider Player::GetAttackBox()
{
	return Collider(attackbox);
}

void Player::Draw(sf::RenderWindow& window)
{
	Entity::Draw(window);

	if(CanAttack())
		window.draw(attackbox);
}