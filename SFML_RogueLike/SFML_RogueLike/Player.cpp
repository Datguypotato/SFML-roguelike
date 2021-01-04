#include "Player.h"

Player::Player(std::vector<Animation*> animations, float speed, int attackDamage)
	:	Entity(sf::Vector2f(50, 80), sf::Vector2f(50, 70), 100, animations, speed, attackDamage),
		weapon(new Weapon(attackDamage, 1.0f)),
		inventory(new Inventory(&body))
{
	body.setPosition(sf::Vector2f(150, 150));
}

Player::~Player()
{
}

Player* Player::Clone() const
{
	return new Player(*this);
}

void Player::Update(float deltaTime)
{
	Entity::Update(deltaTime);
	weapon->Update(deltaTime);

	std::string playName;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		velocity.x -= speed;
		weapon->SetAttackBoxPos(body.getPosition() - sf::Vector2f(body.getSize().x, 0));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		velocity.x += speed;
		weapon->SetAttackBoxPos(body.getPosition() - sf::Vector2f(-body.getSize().x, 0));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		velocity.y += speed;
		weapon->SetAttackBoxPos(body.getPosition() - sf::Vector2f(0, -body.getSize().y));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		velocity.y -= speed;
		weapon->SetAttackBoxPos(body.getPosition() - sf::Vector2f(0, body.getSize().y));
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && weapon->CanAttack())
	{
		AC.PlayNoInterupt("Attack", faceRight);
		weapon->Attack();
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



void Player::Draw(sf::RenderWindow& window)
{
	Entity::Draw(window);

	if(weapon->CanAttack())
		weapon->Draw(window);

	inventory->Draw(window);
}

void Player::CollectItem(Collectable* c)
{
	inventory->GetItem(c->GetItem());
}
