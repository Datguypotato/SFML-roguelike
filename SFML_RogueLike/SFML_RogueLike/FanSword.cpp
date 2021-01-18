#include "FanSword.h"

FanSword::FanSword(sf::Texture* itemText, std::string name)
	:	WeaponItem(itemText, name)
{
	attackDamage = 2;
	minusAttackTimerMax = 0.5f;
}

FanSword::FanSword(sf::Texture* itemText, std::string name, Item* upgrade)
	:	 WeaponItem(itemText, name, upgrade)
{
	attackDamage = 2;
	minusAttackTimerMax = 0.3f;
}

void FanSword::Update(float deltaTime)
{
	for (SlimeBall* projectile : projectiles)
	{
		projectile->Update(deltaTime);
	}
}

void FanSword::CheckCollision(Entity* entity)
{
	Collider coll = entity->GetCollider();
	for (SlimeBall* projectile : projectiles)
	{
		if (projectile->GetCollider().CheckCollision(coll, 0.0f) && projectile->GetAliveStatus())
		{
			OnHit(entity, projectile);
		}
	}
}

// projectile damage dealer
void FanSword::OnHit(Entity* e, SlimeBall* projectile)
{
	e->OnHit(attackDamage / 2);
	projectile->SetAliveStatus(false);
}

void FanSword::DrawProjectiles(sf::RenderWindow& window)
{
	for (SlimeBall* projectile : projectiles)
	{
		projectile->Draw(window);
	}
}


void FanSword::OnAttack(sf::Vector2f startingPos, sf::Vector2f direction)
{
	projectiles.push_back(BuildWindSlash(direction, startingPos + (direction * 10.0f)));
}

std::string FanSword::GetItemStats()
{
	std::string temp = Item::GetItemStats();
	temp += "WindSlash damage: " + std::to_string(attackDamage / 2) + "\n";
	return temp;
}

SlimeBall* FanSword::BuildWindSlash(sf::Vector2f dir, sf::Vector2f startingPos)
{
	std::vector<Animation*> temp = std::vector<Animation*>();
	sf::Texture* texture = new sf::Texture(); 
	texture->loadFromFile("Art/WindSlash.png");
	temp.push_back(new Animation(texture, 1, 1, "Default"));

	SlimeBall* ball = new SlimeBall(temp, dir, attackDamage / 2);
	ball->SetPosition(startingPos);
	projectiles.push_back(ball);

	return ball;
}
