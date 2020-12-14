#include "Goblin.h"

Goblin::Goblin(std::vector<Animation*> animations, sf::Vector2f spawnPosition, sf::RectangleShape* pb, std::function<void(int)> DamagePlayer)
	:	Enemy(sf::Vector2f(66,57), sf::Vector2f(60, 55), 20, animations, pb, 120, DamagePlayer, 10),
		attackRange(100.0f),
		isAttacking(false),
		windupAttackTime(2.0f)
{
	body.setPosition(spawnPosition);

	attackBox.setSize(sf::Vector2f(50, 50));
	attackBox.setOrigin(attackBox.getSize() / 2.0f);
	attackBox.setTexture(nullptr);

	TimeEvent* attackEvent = new TimeEvent(std::bind(&Goblin::Attack, this), windupAttackTime, true);
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
		events[0]->Play();
	}

	if (!isAttacking)
		velocity = GetPlayerDir() * speed;
}

void Goblin::Attack()
{
	if (GetVectorDistance(playerBody->getPosition()) < attackRange)
	{
		Collider pcoll = Collider(*playerBody);
		if (Collider(attackBox).CheckTrigger(pcoll))
			DamagePlayer(attackDamage);
	}
	isAttacking = false;
}

void Goblin::Draw(sf::RenderWindow& window)
{
	Entity::Draw(window);
	window.draw(attackBox);
}