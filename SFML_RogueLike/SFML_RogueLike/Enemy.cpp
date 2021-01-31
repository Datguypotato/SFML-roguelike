#include "Enemy.h"

Enemy::Enemy(sf::Vector2f textureSize, sf::Vector2f bodySize, int health, std::vector<Animation*> animations, Player* player, float speed, int attackDamage, std::string n)
	:	Entity(textureSize, bodySize, health, animations, speed, attackDamage, n)
{
	this->playerBody = player->GetBody();
	this->player = player;
	healthbar = new Healthbar(sf::Vector2f(0, 10), health, true);
}

Enemy::Enemy(const Enemy& rhs)
	:	Entity(rhs)
{
	playerBody = rhs.playerBody;
	player = rhs.player;
	healthbar = rhs.healthbar;
}

Enemy::~Enemy()
{
	playerBody = nullptr;
	player = nullptr;
}

void Enemy::Update(float deltaTime)
{
	Entity::Update(deltaTime);
	healthbar->EntityUpdate(body, health);

	if (damageCooldown <= 0)
		healthbar->SetShowBar(true);
	else
		healthbar->SetShowBar(false);
}

void Enemy::Draw(sf::RenderWindow& window)
{
	Entity::Draw(window);
	healthbar->Draw(window);
}

void Enemy::LookAtPlayer()
{
	if (GetPlayerDir().x > body.getPosition().x)
	{
		faceRight = true;
	}
	else
	{
		faceRight = false;
	}
}

sf::Vector2f Enemy::GetPlayerDir()
{	
	sf::Vector2f delta = (playerBody->getPosition() - body.getPosition());
	float temp = (float)sqrt(delta.x * delta.x + delta.y * delta.y);
	return delta / temp;
}

float Enemy::GetVectorDistance(sf::Vector2f target)
{
	return sqrt(pow(target.x - body.getPosition().x, 2) +
				pow(target.y - body.getPosition().y, 2));
}

void Enemy::UpdateAttackBox()
{
	attackBox.setPosition(body.getPosition() + sf::Vector2f(body.getSize().x * GetPlayerDir().x,
															body.getSize().y * GetPlayerDir().y));
}

void Enemy::AttackPlayer()
{
	Collider pcoll = Collider(*playerBody);
	if(Collider(attackBox).CheckTrigger(pcoll))
		player->OnHit(attackDamage, this);
}