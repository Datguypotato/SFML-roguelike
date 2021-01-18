#include "Goblin.h"

Goblin::Goblin(std::vector<Animation*> animations, sf::Vector2f spawnPosition, Player* player)
	:	Enemy(sf::Vector2f(66,57), sf::Vector2f(60, 55), 5, animations, player, 120, 10, "Goblin"),
		attackRange(100.0f),
		isAttacking(false),
		windupAttackTime(2.0f)
{
	body.setPosition(spawnPosition);

	attackBox.setSize(sf::Vector2f(50, 50));
	attackBox.setOrigin(attackBox.getSize() / 2.0f);
	attackBox.setTexture(nullptr);

	TimeEvent* attackEvent = new TimeEvent(std::bind(&Goblin::Attack, this), windupAttackTime, true, "Attack");
	attackEvent->Pause();
	events.push_back(attackEvent);
}

Goblin::~Goblin()
{
}

void Goblin::Update(float deltaTime)
{
	Entity::Update(deltaTime);
	std::string playName = "Default";

	Action();

	if(!isAttacking)
		Enemy::UpdateAttackBox();

	AC.Play(playName, faceRight);
	AC.UpdateAnimation(deltaTime, faceRight);
	body.move(velocity * deltaTime);
	TextureBody.setPosition(body.getPosition());
}


void Goblin::Action()
{
	if (GetVectorDistance(playerBody->getPosition()) < attackRange && !isAttacking)
	{
		// player in range
		isAttacking = true;
		GetEvent("Attack")->Play();
	}

	if (!isAttacking)
		velocity = GetPlayerDir() * speed;
}

void Goblin::Attack()
{
	if (GetVectorDistance(playerBody->getPosition()) < attackRange)
	{
		AttackPlayer();
	}
	isAttacking = false;
}

void Goblin::Draw(sf::RenderWindow& window)
{
	Entity::Draw(window);
	
	if(isAttacking)
		window.draw(attackBox);
}
