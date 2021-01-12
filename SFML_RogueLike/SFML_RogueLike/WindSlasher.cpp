#include "WindSlasher.h"

WindSlasher::WindSlasher(sf::Texture* itemText, std::string name, SlotRegion* sr)
	:	FanSword(itemText, name, sr)
{
}

void WindSlasher::Update(float deltaTime)
{
	FanSword::Update(deltaTime);

	for (SlimeBall* projectile : projectiles)
	{
		projectile->GetBody()->setScale(sf::Vector2f(deltaTime, deltaTime));
	}
}

std::string WindSlasher::GetItemStats()
{
	std::string temp = FanSword::GetItemStats();
	temp += "*Slashing increasing size over time\n";
	return temp;
}