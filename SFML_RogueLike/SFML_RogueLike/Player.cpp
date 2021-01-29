#include "Player.h"

Player::Player(std::vector<Animation*> animations, float speed, int attackDamage)
	:	Entity(sf::Vector2f(50, 80), sf::Vector2f(50, 70), 100, animations, speed, attackDamage, "Player"),
		weapon(new Weapon(attackDamage, 2.0f)),
		armour(new Armour(weapon)),
		inventory(new Inventory(&body, weapon, armour)),
		attackBoxOffset(sf::Vector2f(-body.getSize().x, 0)),
		facingDirection(sf::Vector2f(0,0)),
		lastFacingDir(sf::Vector2f(0,0))
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
	armour->Update(deltaTime);

	std::string playName;

	facingDirection = sf::Vector2f(0, 0);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		velocity.x -= speed;
		attackBoxOffset = sf::Vector2f(body.getSize().x, 0);
		facingDirection += sf::Vector2f(-1, 0);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		velocity.x += speed;
		attackBoxOffset = sf::Vector2f(-body.getSize().x, 0);
		facingDirection += sf::Vector2f(1, 0);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		velocity.y += speed;
		attackBoxOffset = sf::Vector2f(0, -body.getSize().y);
		facingDirection += sf::Vector2f(0, 1);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		velocity.y -= speed;
		attackBoxOffset = sf::Vector2f(0, body.getSize().y);
		facingDirection += sf::Vector2f(0, -1);
	}


	if (facingDirection == sf::Vector2f(0, 0))
		facingDirection = lastFacingDir;


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		armour->SetRoll();
	}

	armour->OnRoll(this, facingDirection);
	weapon->SetAttackBoxPos(body.getPosition() - attackBoxOffset);


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && weapon->CanAttack())
	{
		AC.PlayNoInterupt("Attack", faceRight);
		weapon->Attack(body.getPosition(), facingDirection);
		armour->SetArmourValue();
		lastFacingDir = facingDirection;
	}

	if (velocity.x != 0.0f || velocity.y != 0.0f)
		playName = "Walk";
	else
		playName = "Default";
	
	//std::cout << "Curr player position: X" << body.getPosition().x << " y" << body.getPosition().y << std::endl;

	AC.Play(playName, faceRight);
	AC.UpdateAnimation(deltaTime, faceRight);
	body.move(velocity * deltaTime);
	TextureBody.setPosition(body.getPosition());
}

void Player::UpdateAttack(std::vector<Entity*> enemies)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z), weapon->CanAttack())
	{
		for (Entity* enemy : enemies)
		{
			Collider eColl = enemy->GetCollider();
			if (weapon->GetAttackBox().CheckTrigger(eColl))
				weapon->GetInRange()->push_back(enemy);
		}
	}
}



void Player::Draw(sf::RenderWindow& window)
{
	Entity::Draw(window);
	inventory->Draw(window);
	weapon->Draw(window);
}

void Player::CollectItem(Collectable* c)
{
	if(!inventory->isFull())
		inventory->GetItem(c->GetItem());
}

void Player::CheckCollision(std::vector<Entity*> enemies)
{
	weapon->CheckCollision(enemies);
	armour->CheckCollision(enemies);
}

void Player::OnHit(const int damage, Entity* damageDealer)
{
	if (damageCooldown <= 0)
	{
		int dmg = damage; // so i can edit the value 

		if (weapon->GetActiveWeapon() != nullptr)
		{
			weapon->OnHit(dmg);
		}

		dmg = armour->OnHit(damage, damageDealer, GetPosition());
		Entity::OnHit(dmg, damageDealer);
	}
}
