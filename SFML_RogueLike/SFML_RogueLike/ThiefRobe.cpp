#include "ThiefRobe.h"

ThiefRobe::ThiefRobe(sf::Texture* itemText, std::string name, Item* upgrade)
	:	ArmourItem(itemText, "ThiefRobe", upgrade)
{
	synergy = new Synergy(Synergy::green);
}

ThiefRobe::ThiefRobe(sf::Texture* itemText, std::string name)
	:	ArmourItem(itemText, "ThiefRobe")
{
	synergy = new Synergy(Synergy::green);
}

void ThiefRobe::Update(float deltaTime)
{
	rollTimer -= deltaTime;

	if (rollTimer <= 0)
	{
		CanRoll = true;
	}

	if (IsRolling)
	{
		rollingTimer -= deltaTime;
		if (rollingTimer <= 0)
			IsRolling = false;
	}
}

void ThiefRobe::OnRoll(Entity* player, sf::Vector2f dir)
{
	if (IsRolling)
	{
		player->GetBody()->move(dir * rollPower);
	}
}

void ThiefRobe::SetRoll()
{
	if (CanRoll)
	{
		CanRoll = false;
		rollTimer = rollTimerMax;
		rollingTimer = rollingTimerMax;
		IsRolling = true;
		std::cout << "Set Roll\n";
	}
}

std::string ThiefRobe::GetItemStats()
{
	return Item::GetItemStats() + "Press X to roll towards a direction\nYou can roll every " + std::to_string(rollingTimerMax) + " seconds\n";
}
