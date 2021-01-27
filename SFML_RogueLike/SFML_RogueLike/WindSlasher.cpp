#include "WindSlasher.h"

WindSlasher::WindSlasher(sf::Texture* itemText, std::string name)
	:	FanSword(itemText, name)
{

}

void WindSlasher::Update(float deltaTime)
{
	FanSword::Update(deltaTime);

	for (Entity* projectile : projectiles)
	{
		if (projectile->GetAliveStatus())
		{
			projectile->SetBodySize(sf::Vector2f(deltaTime * 100, deltaTime * 100) + projectile->GetBody()->getSize());
		}
	}
}

void WindSlasher::OnHit(Entity* e, Entity* projectile)
{
	sf::Vector2f originalSize = sf::Vector2f(50, 50);
	e->OnHit(attackDamage *= projectile->GetBodySize().x / originalSize.x);
	projectile->SetAliveStatus(false);
}

std::string WindSlasher::GetItemStats()
{
	std::string temp = FanSword::GetItemStats();
	temp += "*Slashing increasing size over time\n";
	temp += "*Dealing more damage the bigger it grows";
	return temp;
}