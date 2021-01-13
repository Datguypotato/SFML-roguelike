#include "WindSlasher.h"

WindSlasher::WindSlasher(sf::Texture* itemText, std::string name)
	:	FanSword(itemText, name)
{

}

void WindSlasher::Update(float deltaTime)
{
	FanSword::Update(deltaTime);

	for (SlimeBall* projectile : projectiles)
	{
		if (projectile->GetAliveStatus())
		{
			projectile->SetSize(sf::Vector2f(deltaTime * 100, deltaTime * 100) + projectile->GetBody()->getSize());
		}
	}
}

void WindSlasher::OnHit(Entity* e, SlimeBall* projectile)
{
	sf::Vector2f originalSize = sf::Vector2f(50, 50);
	e->OnHit(damage *= projectile->GetSize().x / originalSize.x);
	projectile->SetAliveStatus(false);
}

std::string WindSlasher::GetItemStats()
{
	std::string temp = FanSword::GetItemStats();
	temp += "*Slashing increasing size over time\n";
	return temp;
}